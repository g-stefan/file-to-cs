# Library

```cpp
#include <XYO/FileToCS.hpp>

namespace XYO::FileToCS {
	bool fileToCpp(const char *stringName, const char *fileNameIn, const char *fileNameOut, bool append, bool isString);
	bool fileToCString(const char *stringName, const char *fileNameIn, const char *fileNameOut);
	bool fileToCStringDirect(const char *fileNameIn, const char *fileNameOut);
};
```

The parameters are `const char *`; a `String` converts to it implicitly.
All three return `true` on success and `false` on any failure, print
nothing and throw nothing. The exact output of each one is in
[Output format](output-format.md).

## fileToCpp

```cpp
// static const uint8_t logoPng[]={...};
XYO::FileToCS::fileToCpp("logoPng", "logo.png", "Logo.Source.cpp", false, false);

// static const char librarySource[]={...,0x00};
XYO::FileToCS::fileToCpp("librarySource", "Library.js", "Library.Source.cpp", false, true);
```

| Parameter | Meaning |
|-----------|---------|
| `stringName` | name of the array, written as given (must be a valid C identifier) |
| `fileNameIn` | input, read as bytes |
| `fileNameOut` | output; its folder must exist |
| `append` | `false`: replace the output; `true`: add to its end (create it if missing) |
| `isString` | `false`: `static const uint8_t`; `true`: `static const char` plus a `0x00` terminator |

Returns `false` if the input can not be opened (the output is then not
touched) or the output can not be opened. Write errors after that (a full
disk) are not detected. It works with C `FILE *` and a fixed size loop,
so files of any size are converted without loading them into memory.

This is the function behind the tool's default and `--is-string` forms.

## fileToCString

```cpp
// static const char *helpText="...";\r\n
XYO::FileToCS::fileToCString("helpText", "help.txt", "Help.Source.cpp");
```

Reads the whole input into a `String`, escapes it with `String::encodeC`
and writes a `static const char *` declaration. The output is always
replaced. It is written in several steps: if one fails the output is left
incomplete and `false` is returned.

Not used by the command line tool.

## fileToCStringDirect

```cpp
// "..."
XYO::FileToCS::fileToCStringDirect("help.txt", "Help.inc");
```

Reads the whole input, writes only the escaped literal (with its quotes,
no declaration, no newline). The output is always replaced. This is the
tool's `--is-string-direct`.

## Regenerate only when changed

The library functions always write. To do what the tool's `--touch` does:

```cpp
if (!Shell::fileExists(out) || Shell::compareLastWriteTime(in, out) > 0) {
	if (!XYO::FileToCS::fileToCpp(name, in, out, false, true)) {
		return false;
	};
	Shell::touchIfExists(includingCpp);
};
```

## Embedding the command line tool

Depend on `file-to-cs.application.static` and call the tool class with an
argument vector, the way fabricare does:

```cpp
#include <XYO/FileToCS.Application.hpp>

int runFileToCS(TDynamicArray<String> &arguments) {
	int cmdN = (int)arguments.length() + 1;
	char **cmdS = new char *[cmdN];
	cmdS[0] = const_cast<char *>("file-to-cs");
	for (int k = 1; k < cmdN; ++k) {
		cmdS[k] = const_cast<char *>(arguments[k - 1].value());
	};
	int retV;
	{
		XYO::FileToCS::Application::Application application;
		retV = application.main(cmdN, cmdS);
	};
	delete[] cmdS;
	return retV;
};
```

`cmdS[0]` is the program name and is skipped. `TDynamicArray` is not
contiguous memory, so build a plain `char *` array. The tool prints to
`stdout` and returns the exit code; it never calls `exit`. The options are
in [Command line](command-line.md).

## Library metadata

As in every XYO library (the headers are not included by
`<XYO/FileToCS.hpp>`):

```cpp
#include <XYO/FileToCS/Version.hpp>
#include <XYO/FileToCS/Copyright.hpp>
#include <XYO/FileToCS/License.hpp>

XYO::FileToCS::Version::version();            // "6.0.0"
XYO::FileToCS::Version::build();
XYO::FileToCS::Version::versionWithBuild();
XYO::FileToCS::Version::datetime();
XYO::FileToCS::Copyright::copyright();
XYO::FileToCS::License::license();            // std::string
```

The tool has the same set in `XYO::FileToCS::Application::Version`,
`Copyright` and `License`.
