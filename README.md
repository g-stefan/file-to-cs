# File to C/C++ Source

Utility and C++ library to convert a file to C/C++ source
- Embeds any file in a program as `static const uint8_t name[]={0x89,...};`,
as a C string `static const char name[]={...,0x00};` (`--is-string`), or as
an escaped string literal `"..."` (`--is-string-direct`).
- `file-to-cs` command line tool: `--name`, `--file-in`, `--file-out`,
`--append` (several arrays in one file), `--touch` (regenerate only when the
input changed, then touch the `.cpp` that includes it), `@file` response files.
- Library `XYO::FileToCS`: `fileToCpp`, `fileToCString`, `fileToCStringDirect`,
and the tool as a class to embed in other programs.

Built on `xyo-system`; used by `fabricare` and `quantum-script` to compile
their JavaScript sources into the executables.

## Documentation

- [Overview](docs/README.md) - purpose and design
- [Getting started](docs/getting-started.md) - build, depend on it, use it in a build, first program
- [Command line](docs/command-line.md) - `file-to-cs` options, `--touch`, `--append`, exit codes, examples
- [Output format](docs/output-format.md) - exact output of each form, escape rules, pitfalls
- [Library](docs/library.md) - `fileToCpp`, `fileToCString`, `fileToCStringDirect`, embedding the tool
- [API reference](docs/reference.md)

A Claude Code skill for this library is in
[.claude/skills/file-to-cs](.claude/skills/file-to-cs/SKILL.md).

## License

Copyright (c) 2007-2026 Grigore Stefan
Licensed under the [MIT](LICENSE) license.
