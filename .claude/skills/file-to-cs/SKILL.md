---
name: file-to-cs
description: >-
  How to use file-to-cs, the XYO tool and C++ library (namespace
  XYO::FileToCS) on top of xyo-system that converts any file into C/C++
  source to embed it in a binary: the file-to-cs command line (--name,
  --file-in, --file-out, --is-string, --is-string-direct, --append,
  --touch, @response files, exit codes); the three output forms (static
  const uint8_t name[]={0xHH,...}; static const char name[]={...,0x00};
  an escaped "..." literal from String::encodeC); the functions fileToCpp,
  fileToCString, fileToCStringDirect; embedding the tool through
  file-to-cs.application.static and XYO::FileToCS::Application::Application
  (fabricare's fileToCS(...)); the make.prepare.js pattern that generates
  *.Source.cpp from *.js with --touch. Use when writing or reviewing code
  that includes <XYO/FileToCS.hpp> or <XYO/FileToCS.Application.hpp>,
  depends on "file-to-cs" in fabricare.json, calls file-to-cs or fileToCS
  in a build script, #includes a generated *.Source.cpp, wants to embed a
  script / text / binary file in C++ code, or when working inside the
  file-to-cs repository.
---

# file-to-cs

Converts a file into C/C++ source so it is compiled into the program. Two
faces:

- the **`file-to-cs` command line tool**, run from
  `fabricare/make.prepare.js` (fabricare, quantum-script and its
  extensions embed their `.js` files this way);
- the **C++ library** `XYO::FileToCS`: `fileToCpp`, `fileToCString`,
  `fileToCStringDirect`, plus the tool as a class.

Built on `xyo-system` (see the `xyo-system` skill and the layers below it:
their rules apply).

Full documentation: `docs/` in the file-to-cs repository
(`X:\Storage\XYO\Gitea\CPP\file-to-cs\docs` on this machine): README,
getting-started, **command-line**, **output-format**, library, reference.
The whole implementation is `source/XYO/FileToCS/Library.cpp` and
`source/XYO/FileToCS.Application/Application.cpp`.

## Pick a form

| Need | Command line | C++ | Output |
|------|--------------|-----|--------|
| Binary file (image, font, zip) | `--name=n` | `fileToCpp(n, in, out, false, false)` | `static const uint8_t n[]={0x89,...};` size = file size |
| Text used as `const char *` (scripts) | `--name=n --is-string` | `fileToCpp(n, in, out, false, true)` | `static const char n[]={...,0x00};` size = file size + 1 |
| Readable escaped literal | `--is-string-direct` (no `--name`) | `fileToCStringDirect(in, out)` | `"..."` only, no `;`, no newline |
| Declaration with a literal | | `fileToCString(n, in, out)` | `static const char *n="...";\r\n` |
| Several arrays in one file | first call plain, the rest `--append` | `append = true` | arrays one after another |
| Regenerate only if input newer | `--touch=Including.cpp` | `Shell::compareLastWriteTime(in, out) > 0` | touches `Including.cpp` after writing |

## The standard build pattern

`fabricare/make.prepare.js`:

```js
messageAction("make.prepare");

runInPath("source/XYO/MyTool", function() {
	exitIf(Shell.system("file-to-cs --touch=Library.cpp --file-in=Library.js --file-out=Library.Source.cpp --is-string --name=librarySource"));
});
```

`source/XYO/MyTool/Library.cpp`:

```cpp
#include <XYO/MyTool/Library.Source.cpp>
// ...
executive->compileStringX(librarySource);
```

Inside fabricare scripts the tool is also built in:
`exitIf(fileToCS("--file-in=a.js", "--file-out=a.Source.cpp", "--is-string", "--name=aSource"));`
(one argument per parameter, returns the exit code).

Literal form:

```cpp
static const char *helpText =
#include "Help.inc"
;
```

## Hard rules

1. **Required options**: `--file-in`, `--file-out`, and `--name` unless
   `--is-string-direct`. Missing → usage printed, exit `1`. Empty value
   (`--name=`) → error, exit `1`.
2. **`--is-string-direct` wins**: it ignores `--name`, `--is-string` and
   `--append`, and always replaces the output.
3. **Failures**: the tool prints `Error: file not found - <in>`,
   `Error: directory not found - <out folder>` or `Error: unable to read
   <in> or write <out>` and exits `1`; the library functions just return
   `false`, no message. Always `exitIf(...)` / check the result. The
   output folder is never created, it must already exist.
4. **`--touch=f`**: if the output exists and the input is **not newer**,
   exit `0` and do nothing (not even touch). Otherwise write, then touch
   `f` only if it exists. Point it at the `.cpp` that `#include`s the
   generated file so incremental builds recompile it.
5. **`--append` accumulates**: every run adds again. Start each sequence
   with one call without `--append`. Do not mix `--append` with `--touch`
   on a shared output (later inputs get compared to the already written
   file and skipped).
6. **`--is-string` with bytes ≥ `0x80`** (UTF-8, Latin-1) is a C++11
   narrowing into signed `char`: GCC **error** (only a warning with
   `-fpermissive`, which xyo-cc passes), MSVC warning C4838. Keep those
   inputs ASCII, or use the `uint8_t` form, or `--is-string-direct`.
7. **Empty input with the byte form** gives a zero size array: MSVC error
   C2466. `--is-string` gives `{0x00}` and is fine.
8. **Names are not checked**: `--name` must be a valid C identifier and
   unique in the translation unit (`my-logo` → compile error; sanitize).
9. **Arrays are `static`**: include a generated file in one `.cpp` only,
   expose it through a function if others need it. `uint8_t` needs
   `<stdint.h>` (any XYO header brings it).
10. **Escape rules** of the literal forms (`String::encodeC`): `\\` `\"`
    `\n` `\r` `\t`, printable ASCII as is (`'` not escaped), everything
    else `\xHH`, and a hex digit right after `\xHH` is escaped too
    (`"\xAB\x31"`, since C hex escapes are greedy). `0x00` is kept as
    `\x00` but ends the string for C string functions.
11. **Generated files** (`*.Source.cpp`, `.inc`) are outputs: never edit
    them, edit the input and rebuild.
12. **`@file`** response files are expanded first (split like a command
    line, quotes group words); a missing one → `Error: file not found -
    file`, exit `1`. Unknown options and non `--` arguments are ignored.

## Depend on it

```json
"dependency": [ "file-to-cs" ]                    // DLL
"dependency": [ "file-to-cs.static" ]             // static, defines XYO_FILETOCS_LIBRARY
"dependency": [ "file-to-cs.application.static" ] // embed the tool, no main
```

```cpp
#include <XYO/FileToCS.hpp>

if (!XYO::FileToCS::fileToCpp("logoPng", "logo.png", "Logo.Source.cpp", false, false)) {
	printf("* Error: logo.png\n");
	return 1;
};
```

Embedded tool (as fabricare's `fileToCS(...)`): build a plain `char *`
array (`cmdS[0]` = program name, `TDynamicArray` is not contiguous) and
call `XYO::FileToCS::Application::Application application;
application.main(cmdN, cmdS)` — it returns the exit code and prints to
stdout.

Metadata: `XYO::FileToCS::Version::version()` from
`<XYO/FileToCS/Version.hpp>` (not included by `<XYO/FileToCS.hpp>`); the
tool's is `XYO::FileToCS::Application::Version::version()`.

## Working inside this repository

- Four projects in `fabricare.json`: `file-to-cs` (DLL, version key
  `file-to-cs.library`), `file-to-cs.static`,
  `file-to-cs.application.static`, `file-to-cs` (exe).
- `fabricare make`, `fabricare install`. There is no test project; try
  changes with the built `output/bin/file-to-cs` on sample inputs and
  compile the result.
- fabricare bootstraps this tool without itself
  (`build/file-to-cs.compile.json` in the fabricare repository): keep
  `FileToCS.Application.Amalgam.cpp` self-contained.
- Keep the docs in `docs/` and this skill in step with `Library.hpp` /
  `Application.cpp` when behavior changes.
- Licensing follows REUSE: `source/`, `docs/` and `README.md` are MIT
  (source files also carry SPDX headers); build scripts, config,
  `version.json` and `.claude/` are Unlicense. Every new top level file or
  folder needs a `Files:` entry in `.reuse/dep5` (check with `reuse lint`).
