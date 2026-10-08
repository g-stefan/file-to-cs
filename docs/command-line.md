# Command line

```
file-to-cs [options] [@file ...]
```

## Options

| Option | Effect |
|--------|--------|
| `--help`, `--usage` | print usage, exit 0 |
| `--license` | print the license, exit 0 |
| `--version` | print the tool's own version, exit 0 |
| `--name=name` | name of the generated array; required unless `--is-string-direct` |
| `--file-in=file` | input file, any content; required |
| `--file-out=file` | output file; required; its folder must exist |
| `--is-string` | `static const char name[]` with a `0x00` terminator, instead of `static const uint8_t name[]` |
| `--is-string-direct` | write only an escaped C string literal `"..."`; `--name`, `--is-string` and `--append` are ignored |
| `--append` | add the array to the end of the output instead of replacing it |
| `--touch=file` | regenerate only if the input is newer than the output; afterwards touch `file` |
| `@file` | read more arguments from `file` (a response file) |

`--help`, `--usage`, `--license` and `--version` act as soon as they are
seen. Arguments that do not start with `--` (other than `@file`) and
unknown options are ignored. An empty `--name=`, `--file-in=`,
`--file-out=` or `--touch=` is an error. When a required option is
missing, the usage is printed and the exit code is `1`.

The exact output of each form is in [Output format](output-format.md).

## Order of work

1. Expand the `@file` response files, then read the options.
2. Check `--name` (unless `--is-string-direct`), `--file-in`, `--file-out`.
3. `--touch`: if the output exists and the input is **not newer** than it,
   stop with exit code `0`; nothing is written or touched.
4. Write the output: `--is-string-direct`, else the array (`uint8_t` or,
   with `--is-string`, `char`), replacing or (`--append`) appending.
5. `--touch`: touch the file if it exists (a missing one is not an error).

## --touch

Generated files are `#include`d by a hand written `.cpp`. A build tool
that checks only the time of the `.cpp` will not see a change in the
generated file, and regenerating on every build changes its time and
recompiles it every time. `--touch=Library.cpp` handles both:

- input not newer than output → nothing happens, the build stays
  incremental;
- input newer, or no output yet → the output is written and
  `Library.cpp` gets the current time, so it is recompiled.

The check compares the last write time of `--file-in` and `--file-out`
(`Shell::compareLastWriteTime`, nanoseconds on Linux).

Do not combine `--touch` with `--append` on a shared output: once the
first input has written the file, the next ones are compared against it
and skipped.

## --append

```
file-to-cs --name=iconOpen --file-in=open.png --file-out=Icons.Source.cpp
file-to-cs --name=iconSave --file-in=save.png --file-out=Icons.Source.cpp --append
file-to-cs --name=iconExit --file-in=exit.png --file-out=Icons.Source.cpp --append
```

The first call replaces the output, the next ones add to it. Every run of
an `--append` call adds again: start the sequence with a call without
`--append` (or remove the output first), or the file collects duplicate
definitions.

## Exit codes

| Code | Meaning |
|------|---------|
| `0` | written; also up to date (`--touch`), and `--help` / `--usage` / `--license` / `--version` |
| `1` | missing or empty required option, response file not found, input can not be read, output can not be written |

Errors are printed to `stdout`. The library functions only report
success or failure, so after a failed conversion the tool looks for the
most likely cause:

| Message | Cause |
|---------|-------|
| `Error: file not found - <file-in>` | the input does not exist (or is a directory) |
| `Error: directory not found - <folder>` | the folder of `--file-out` does not exist (it is not created) |
| `Error: unable to read <file-in> or write <file-out>` | anything else: no access to the input, output read-only or a directory, ... |

The other errors are `Error: name is empty`, `Error: file-in is empty`,
`Error: file-out is empty`, `Error: touch filename is empty` and
`Error: file not found - <file>` for a response file.

## Response files

`@file` is replaced by the arguments read from `file`, split like a command
line (quotes group words). Several `@file` and normal arguments can be
mixed:

```
--name=librarySource
--file-in=Library.js
"--file-out=Library.Source.cpp"
--is-string
```

```
file-to-cs @library.args --touch=Library.cpp
```

## From fabricare

In a `fabricare/make.prepare.js` script, the tool is on the `PATH` of the
build:

```js
runInPath("source/XYO/QuantumScript", function() {
	exitIf(Shell.system("file-to-cs --touch=LibStdArray.cpp --file-in=LibStdArray.js --file-out=LibStdArray.Source.cpp --is-string --name=libStdArraySource"));
});
```

Inside fabricare itself the tool is linked in
(`file-to-cs.application.static`) and is also available to scripts as the
function `fileToCS(...)`, which takes the same arguments as strings, one
per parameter, and returns the exit code:

```js
exitIf(fileToCS("--touch=Library.cpp", "--file-in=Library.js", "--file-out=Library.Source.cpp", "--is-string", "--name=librarySource"));
```

## Examples

A script, as a C string:

```
file-to-cs --name=librarySource --file-in=Library.js --file-out=Library.Source.cpp --is-string
```

A binary file:

```
file-to-cs --name=logoPng --file-in=logo.png --file-out=Logo.Source.cpp
```

An escaped literal, to use inside an expression:

```
file-to-cs --file-in=help.txt --file-out=Help.inc --is-string-direct
```

```cpp
static const char *helpText =
#include "Help.inc"
;
```

Only when the script changed:

```
file-to-cs --touch=Library.cpp --file-in=Library.js --file-out=Library.Source.cpp --is-string --name=librarySource
```
