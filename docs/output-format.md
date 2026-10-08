# Output format

The examples below use this 22 byte input, `script.js`:

```
print("hi");
	x="a\b";
```

(the `\b` is a backspace byte, `0x08`, to show how control bytes are
written).

## Byte array (default)

```
file-to-cs --name=data --file-in=script.js --file-out=Data.Source.cpp
```

```cpp
static const uint8_t data[]={
	0x70,0x72,0x69,0x6E,0x74,0x28,0x22,0x68,0x69,0x22,0x29,0x3B,0x0A,0x09,0x78,0x3D,0x22,0x61,0x08,0x22,0x3B,0x0A
};
```

- `static const uint8_t`, one `0xHH` (upper case hex) per input byte, 32
  per line, tab indented, `\n` line ends.
- The bytes are copied exactly: no text mode, no encoding, no
  terminator. `sizeof(data)` is the file size.
- `uint8_t` needs `<stdint.h>` / `<cstdint>` before the include; any XYO
  header brings it.

Use it:

```cpp
#include <XYO/MyTool/Data.Source.cpp>

Buffer buffer;
buffer.set(data, sizeof(data));               // or MemoryRead, fwrite, ...
```

## String array (`--is-string`)

```
file-to-cs --name=text --file-in=script.js --file-out=Text.Source.cpp --is-string
```

```cpp
static const char text[]={
	0x70,0x72,0x69,0x6E,0x74,0x28,0x22,0x68,0x69,0x22,0x29,0x3B,0x0A,0x09,0x78,0x3D,0x22,0x61,0x08,0x22,0x3B,0x0A,0x00
};
```

The same bytes as `char`, plus a final `0x00`, so `text` is a C string:
`sizeof(text)` is the file size **plus one**, `strlen(text)` the file
size (if the file has no `0x00` byte of its own). This is the form used
by fabricare and quantum-script to embed their JavaScript:

```cpp
#include <XYO/QuantumScript/LibStdArray.Source.cpp>
// ...
executive->compileStringX(libStdArraySource);
```

A file whose size is a multiple of 32 puts the terminator on its own line
(`	,0x00`); that is valid C++.

## String literal (`--is-string-direct`)

```
file-to-cs --file-in=script.js --file-out=Text.inc --is-string-direct
```

```
"print(\"hi\");\n\tx=\"a\x08\";\n"
```

Only the literal, on one line, without a declaration, a `;` or a final
newline. Include it where an expression is expected:

```cpp
static const char *text =
#include "Text.inc"
;
```

Escape rules (`String::encodeC` from `xyo-encoding`):

| Byte | Written as |
|------|------------|
| `\` | `\\` |
| `"` | `\"` |
| line feed, carriage return, tab | `\n`, `\r`, `\t` |
| other printable ASCII `0x20`..`0x7E`, also `'` | itself |
| anything else (control bytes, `0x00`, `0x80`..`0xFF`) | `\xHH` |
| a hex digit `0-9 A-F a-f` right after a `\xHH` | `\xHH` too |

The last rule exists because C hex escapes are greedy: `"\xAB1"` would be
read as the single escape `\xAB1`. So the bytes `A 0xAB 1 B 0x00 Z` give
`"A\xAB\x31\x42\x00Z"`.

A `0x00` byte in the file is kept in the literal, but code that treats the
result as a C string stops there. A UTF-8 file is written byte by byte
(`é` is `\xC3\xA9`) and stays UTF-8 at run time.

## `fileToCString` (library only)

`XYO::FileToCS::fileToCString("text", in, out)` writes a declaration with
the literal above and a `\r\n` line end:

```cpp
static const char *text="print(\"hi\");\n\tx=\"a\x08\";\n";
```

It is not reachable from the command line.

## Appending

With `--append` (library: `append = true`) the next array is written right
after the previous one:

```cpp
static const char text[]={
	...
};
static const uint8_t logo[]={
	...
};
```

Each name must be unique in the file. `--is-string-direct` and
`fileToCString` always replace the output.

## Pitfalls

| Situation | What happens | Do this |
|-----------|--------------|---------|
| `--is-string` on a file with bytes `0x80`..`0xFF` (UTF-8 text, Latin-1) | `char` is signed: `0xC3` does not fit, a C++11 narrowing conversion. GCC: **error** (warning with `-fpermissive`, which xyo-cc uses); MSVC: warning C4838. The value at run time is still the right byte | keep `--is-string` inputs ASCII, or use the byte array and cast: `(const char *)data` (add your own terminator), or `--is-string-direct` |
| empty input, byte array | `static const uint8_t data[]={` and `};` with nothing between — a zero size array: MSVC error C2466, GCC accepts it as an extension | do not embed empty files, or use `--is-string` (gives `{0x00}`) |
| two arrays with the same name in one translation unit | redefinition error | unique `--name` per file / per `--append` |
| a name that is not a C identifier (`my-logo`, `2d`) | compile error in the generated file | the name is written as given; sanitize it |
| including the generated file in two `.cpp` files | each gets its own `static` copy (more size, no link error) | include it in one `.cpp` and expose a function |
| `--append` run again on the next build | the output grows, duplicate definitions | start every sequence with one call without `--append` |
