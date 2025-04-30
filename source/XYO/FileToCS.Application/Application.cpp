// File to CS
// Copyright (c) 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToCS.hpp>
#include <XYO/FileToCS.Application/Application.hpp>
#include <XYO/FileToCS.Application/Copyright.hpp>
#include <XYO/FileToCS.Application/License.hpp>
#include <XYO/FileToCS.Application/Version.hpp>

namespace XYO::FileToCS::Application {

	void Application::showUsage() {
		printf("FileToCS - Convert file to C/C++ source\n");
		showVersion();
		printf("%s\n\n", FileToCS::Application::Copyright::copyright());

		printf("%s",
		       "options:\n"
		       "    --help              this info\n"
		       "    --usage             this info\n"
		       "    --license           show license\n"
		       "    --version           show version\n"
		       "    --name=name         string variable name\n"
		       "    --file-in=file      input file\n"
		       "    --file-out=file     output file\n"
		       "    --touch=file        touch file if changed input file\n"
		       "    --append            append content\n"
		       "    --is-string         encode as string\n"
		       "    --is-string-direct  encode as c string with escape codes\n");
		printf("\n");
	};

	void Application::showLicense() {
		printf("%s", FileToCS::Application::License::license().c_str());
	};

	void Application::showVersion() {
		printf("version %s build %s [%s]\n", FileToCS::Application::Version::version(), FileToCS::Application::Version::build(), FileToCS::Application::Version::datetime());
	};

	void Application::initMemory() {
		String::initMemory();
		TDynamicArray<String>::initMemory();
	};

	int Application::main(int cmdN, char *cmdS[]) {
		int i;
		String opt;
		size_t optIndex;
		String optValue;
		TDynamicArray<String> cmdLine;

		String stringName;
		String fileNameIn;
		String fileNameOut;
		bool append = false;
		bool isString = false;
		bool isTouch = false;
		String touchFileName;
		bool isStringDirect = false;

		for (i = 1; i < cmdN; ++i) {
			if (StringCore::beginWith(cmdS[i], "@")) {
				String content;
				if (Shell::fileGetContents(&cmdS[i][1], content)) {
					XYO::System::ShellArguments shellArguments;
					int m;
					shellArguments.set(content);
					for (m = 0; m < shellArguments.cmdN; ++m) {
						cmdLine.push(shellArguments.cmdS[m]);
					};
					continue;
				};
				printf("Error: file not found - %s\n", &cmdS[i][1]);
				return 1;
			};
			cmdLine.push(cmdS[i]);
		};

		for (i = 0; i < cmdLine.length(); ++i) {
			if (StringCore::beginWith(cmdLine[i], "--")) {
				opt = cmdLine[i].index(2);
				optValue = "";
				if (opt.indexOf("=", 0, optIndex)) {
					optValue = opt.substring(optIndex + 1);
					opt = opt.substring(0, optIndex);
				};
				if (opt == "help") {
					showUsage();
					return 0;
				};
				if (opt == "usage") {
					showUsage();
					return 0;
				};
				if (opt == "license") {
					showLicense();
					return 0;
				};
				if (opt == "version") {
					showVersion();
					return 0;
				};
				if (opt == "name") {
					stringName = optValue;
					if (stringName.length() == 0) {
						printf("Error: name is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "file-in") {
					fileNameIn = optValue;
					if (fileNameIn.length() == 0) {
						printf("Error: file-in is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "file-out") {
					fileNameOut = optValue;
					if (fileNameOut.length() == 0) {
						printf("Error: file-out is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "touch") {
					isTouch = true;
					touchFileName = optValue;
					if (touchFileName.length() == 0) {
						printf("Error: touch filename is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "append") {
					append = true;
					continue;
				};
				if (opt == "is-string") {
					isString = true;
					continue;
				};
				if (opt == "is-string-direct") {
					isStringDirect = true;
					continue;
				};
				continue;
			};
		};

		// ---

		if (((stringName.length() == 0) && (!isStringDirect)) ||
		    fileNameIn.length() == 0 ||
		    fileNameOut.length() == 0) {
			showUsage();
			return 1;
		};

		if (isTouch) {
			if (Shell::fileExists(fileNameOut)) {
				if (Shell::compareLastWriteTime(fileNameIn, fileNameOut) <= 0) {
					return 0;
				};
			};
		};

		if (!isStringDirect) {
			if (!fileToCpp(
			        stringName,
			        fileNameIn,
			        fileNameOut,
			        append,
			        isString)) {
				return 1;
			};
		} else {
			if (!fileToCStringDirect(
			        fileNameIn,
			        fileNameOut)) {
				return 1;
			};
		};

		if (isTouch) {
			Shell::touchIfExists(touchFileName);
		};

		return 0;
	};
};

#ifndef XYO_FILETOCS_APPLICATION_LIBRARY
XYO_APPLICATION_MAIN(XYO::FileToCS::Application::Application);
#endif
