# API reference

## Headers

| Header | Contents |
|--------|----------|
| `<XYO/FileToCS.hpp>` | the library: `Dependency.hpp` + `Library.hpp` |
| `<XYO/FileToCS/Copyright.hpp>`, `License.hpp`, `Version.hpp` | library metadata (not included by `FileToCS.hpp`) |
| `<XYO/FileToCS.Application.hpp>` | the library + `XYO::FileToCS::Application::Application` |

## Macros

| Macro | Meaning |
|-------|---------|
| `XYO_FILETOCS_EXPORT` | `dllexport` / `dllimport` / nothing |
| `XYO_FILETOCS_DLL_INTERNAL` | building the DLL (exports); set from `FILE_TO_CS_DLL_INTERNAL`, which xyo-cc defines from the project name |
| `XYO_FILETOCS_INTERNAL` | set from `FILE_TO_CS_INTERNAL`; not used by the sources |
| `XYO_FILETOCS_LIBRARY` | static use, `XYO_FILETOCS_EXPORT` is empty (set by `file-to-cs.static`) |
| `XYO_FILETOCS_APPLICATION_LIBRARY` | build the tool without `main` (set by `file-to-cs.application.static`) |

## namespace XYO::FileToCS

`using namespace XYO::System;`

| Function | Writes | Returns |
|----------|--------|---------|
| `bool fileToCpp(const char *stringName, const char *fileNameIn, const char *fileNameOut, bool append, bool isString)` | `static const uint8_t name[]={0xHH,...};` or, `isString`, `static const char name[]={0xHH,...,0x00};`; appends if `append` | `false` if input or output can not be opened |
| `bool fileToCString(const char *stringName, const char *fileNameIn, const char *fileNameOut)` | `static const char *name="escaped";\r\n` | `false` on read / write failure |
| `bool fileToCStringDirect(const char *fileNameIn, const char *fileNameOut)` | `"escaped"` | `false` on read / write failure |

Escaping is `String::encodeC`: `\\`, `\"`, `\n`, `\r`, `\t`, printable
ASCII as is, everything else `\xHH`, and a hex digit after `\xHH` also as
`\xHH`. Details: [Output format](output-format.md).

## namespace XYO::FileToCS::Version / Copyright / License

```cpp
const char *XYO::FileToCS::Version::version();
const char *XYO::FileToCS::Version::build();
const char *XYO::FileToCS::Version::versionWithBuild();
const char *XYO::FileToCS::Version::datetime();

const char *XYO::FileToCS::Copyright::copyright();
const char *XYO::FileToCS::Copyright::publisher();
const char *XYO::FileToCS::Copyright::company();
const char *XYO::FileToCS::Copyright::contact();

std::string XYO::FileToCS::License::license();
std::string XYO::FileToCS::License::shortLicense();
```

The same functions exist for the tool in
`XYO::FileToCS::Application::Version`, `Copyright` and `License`.

## class XYO::FileToCS::Application::Application

```cpp
class Application : public virtual IApplication {
	public:
		void showUsage();
		void showLicense();
		void showVersion();
		int main(int cmdN, char *cmdS[]);
		static void initMemory();
};
```

The `file-to-cs` command line tool; `main` returns the exit code. See
[Command line](command-line.md).

## Command line options

`--help`, `--usage`, `--license`, `--version`, `--name=name`,
`--file-in=file`, `--file-out=file`, `--is-string`, `--is-string-direct`,
`--append`, `--touch=file`, `@file`.

| Exit code | Meaning |
|-----------|---------|
| `0` | written, up to date (`--touch`), or an info option |
| `1` | missing / empty option, response file not found, read or write failed |

## fabricare projects

| Project | Kind | Defines exported to the consumer |
|---------|------|----------------------------------|
| `file-to-cs` | DLL / shared library, version key `file-to-cs.library` | |
| `file-to-cs.static` | static library, static CRT | `XYO_FILETOCS_LIBRARY` |
| `file-to-cs.application.static` | static library, tool without `main` | `XYO_FILETOCS_APPLICATION_LIBRARY` |
| `file-to-cs` | executable | |
