# Getting started

## 1. Build and install

The library and the tool are built with
[fabricare](https://github.com/g-stefan/fabricare). `xyo-platform`,
`xyo-managed-memory`, `xyo-data-structures`, `xyo-multithreading`,
`xyo-encoding` and `xyo-system` must be installed to the SDK first. From
the repository root:

```bash
fabricare make       # build into output/
fabricare install    # copy output/{bin,include,lib} to ~/.fabricare/<platform>
fabricare clean      # remove output/ and temp/
```

After `install`, `file-to-cs` is in `~/.fabricare/<platform>/bin`, which
is on the `PATH` of a fabricare build, so the `make.prepare.js` scripts of
other projects can call it.

Four projects are produced (`fabricare.json`):

| Project | Kind | Use it when |
|---------|------|-------------|
| `file-to-cs` | DLL / shared library (`dll-or-lib`), the library | default, shared between several programs |
| `file-to-cs.static` | static library, static CRT | self-contained executables |
| `file-to-cs.application.static` | static library with the command line tool, no `main` | embed `file-to-cs` into another tool (fabricare does) |
| `file-to-cs` | executable | the `file-to-cs` command |

The DLL and the executable share the name `file-to-cs`, so the library
keeps its version under the key `file-to-cs.library` in `version.json`
(`"versionName"`); `file-to-cs.static` reuses it and
`file-to-cs.application.static` reuses the executable's (`"linkVersion"`).

## 2. Use the tool in a build

The usual case: a project keeps a script as a normal `.js` file in its
source folder and compiles it in. In the project's
`fabricare/make.prepare.js`:

```js
messageAction("make.prepare");

runInPath("source/XYO/MyTool", function() {
	exitIf(Shell.system("file-to-cs --touch=Library.cpp --file-in=Library.js --file-out=Library.Source.cpp --is-string --name=librarySource"));
});
```

and in `source/XYO/MyTool/Library.cpp`:

```cpp
#include <XYO/MyTool/Library.Source.cpp>

// ...
executive->compileStringX(librarySource);   // static const char librarySource[]={...,0x00};
```

`Library.Source.cpp` is generated: list it in `.gitignore` or commit it,
but never edit it. `--touch=Library.cpp` regenerates it only when
`Library.js` is newer and then touches `Library.cpp`, so the incremental
build recompiles the file that includes it. See
[Command line](command-line.md).

## 3. Depend on the library from another fabricare project

In the consumer's `fabricare.json`:

```json
{
	"name": "my-packer",
	"make": "exe",
	"sourcePath": "XYO/MyPacker",
	"dependency": [
		"file-to-cs"
	]
}
```

For the static variant use `"file-to-cs.static"`; it exports
`XYO_FILETOCS_LIBRARY` to the consumer (`dependencyDefines`), which turns
`XYO_FILETOCS_EXPORT` into nothing. To embed the command line tool use
`"file-to-cs.application.static"` (exports
`XYO_FILETOCS_APPLICATION_LIBRARY`, which leaves out `main`). `xyo-system`
and the layers below come in as transitive dependencies.

## 4. Include

```cpp
#include <XYO/FileToCS.hpp>               // the library
#include <XYO/FileToCS.Application.hpp>   // the library + the command line tool class
```

Namespace `XYO::FileToCS` contains `using namespace XYO::System;`, so
`String`, `Shell::`, `IApplication`, ... are visible inside it.

Call the functions qualified, `XYO::FileToCS::fileToCpp(...)`. The
metadata namespaces exist in every XYO layer; here the library version is
`XYO::FileToCS::Version::version()` and the tool's is
`XYO::FileToCS::Application::Version::version()`.

## 5. First program

A tool that embeds every `.png` of a folder into one generated source file,
one array per image:

```cpp
#include <XYO/FileToCS.hpp>

using namespace XYO::System;

class Application : public virtual IApplication {
		XYO_PLATFORM_DISALLOW_COPY_ASSIGN_MOVE(Application);

	public:
		inline Application(){};

		int main(int cmdN, char *cmdS[]);
};

int Application::main(int cmdN, char *cmdS[]) {
	TDynamicArray<String> fileList;
	Shell::getFileList("images/*.png", fileList);

	String output = "Images.Source.cpp";
	Shell::removeFile(output);

	for (size_t k = 0; k < fileList.length(); ++k) {
		// images/logo.png -> image_logo
		String name = String("image_") + Shell::getFileBasename(Shell::getFileName(fileList[k]));
		// append = true: every call adds one more array to the same file
		if (!XYO::FileToCS::fileToCpp(name, fileList[k], output, true, false)) {
			printf("* Error: %s\n", fileList[k].value());
			return 1;
		};
	};
	return 0;
};

XYO_APPLICATION_MAIN(Application);
```

`XYO_APPLICATION_MAIN` comes from `xyo-system`: it initializes the managed
memory registry and calls `Application::main`. The array name must be a
valid C identifier: a file name such as `my-logo.png` needs its `-`
replaced first.

## 6. Conventions

- **`bool` means success.** Every function returns `false` when the input
  can not be read or the output can not be written; there are no
  exceptions and no message. The tool prints an `Error: ...` line and
  returns exit code `1` (see [Command line](command-line.md#exit-codes)).
- **Paths are used as given**, relative to the current directory. The
  output folder must exist.
- **The output is overwritten** unless `append` / `--append` is used.
- **Names are not checked.** `--name` / `stringName` is written as is: it
  must be a valid, unique C identifier.
- **Nothing is cached, no locking.** Do not write the same output file from
  two processes at the same time.

## 7. Building without fabricare

The tool is one translation unit plus the XYO layers. This is how
fabricare bootstraps itself (`build/file-to-cs.compile.json` in the
fabricare repository):

1. Put `source/` of `xyo-platform`, `xyo-managed-memory`,
   `xyo-data-structures`, `xyo-multithreading`, `xyo-encoding`,
   `xyo-system` and `file-to-cs` on the include path, with the
   configuration headers of the layers that need them (see their
   documentation).
2. Define `XYO_PLATFORM_LIBRARY`, `XYO_MANAGEDMEMORY_LIBRARY`,
   `XYO_DATASTRUCTURES_LIBRARY`, `XYO_MULTITHREADING_LIBRARY`,
   `XYO_ENCODING_LIBRARY`, `XYO_SYSTEM_LIBRARY` and `XYO_FILETOCS_LIBRARY`
   (static, no DLL export).
3. Compile `FileToCS.Application.Amalgam.cpp` with
   `Platform.Amalgam.cpp`, `ManagedMemory.Amalgam.cpp`,
   `DataStructures.Amalgam.cpp`, `Multithreading.Amalgam.cpp`,
   `Encoding.Amalgam.cpp` and `System.Amalgam.cpp` as C++17.

For the library only, compile `FileToCS.Amalgam.cpp` instead of
`FileToCS.Application.Amalgam.cpp`.
