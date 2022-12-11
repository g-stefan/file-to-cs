// File to CS
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToCS/Library.hpp>

namespace XYO::FileToCS {

	bool fileToCpp(const char *stringName, const char *fileNameIn, const char *fileNameOut, bool append, bool isString) {

		FILE *input;
		FILE *output;
		uint8_t ch;
		int index;
		int first;

		input = fopen(fileNameIn, "rb");
		if (input != nullptr) {
			output = fopen(fileNameOut, append ? "ab" : "wb");
			if (output != nullptr) {
				if (isString) {
					fprintf(output, "static const char %s[]={", stringName);
				} else {
					fprintf(output, "static const uint8_t %s[]={", stringName);
				};

				ch = 0x00;
				index = 0;
				first = 1;
				while (fread(&ch, 1, 1, input) == 1) {

					if (first) {
						first = 0;
						fprintf(output, "\n\t");
					} else {
						fprintf(output, ",");
						if (index == 0) {
							fprintf(output, "\n\t");
						};
					};

					fprintf(output, "0x%02X", ch);

					++index;
					index %= 32;

					ch = 0;
				};

				if (index == 0) {
					fprintf(output, "\n\t");
				};

				++index;
				index %= 32;

				if (isString) {
					if (!first) {
						fprintf(output, ",");
					};
					fprintf(output, "0x00");
				};

				fprintf(output, "\n};\n");
				fclose(output);
				fclose(input);
				return true;
			};
			fclose(input);
		};
		return false;
	};

	bool fileToCString(const char *stringName, const char *fileNameIn, const char *fileNameOut) {
		String content;
		if (Shell::fileGetContents(fileNameIn, content)) {
			if (Shell::filePutContents(fileNameOut, "static const char *")) {
				if (Shell::filePutContentsAppend(fileNameOut, stringName)) {
					if (Shell::filePutContentsAppend(fileNameOut, "=")) {
						if (Shell::filePutContentsAppend(fileNameOut, String::encodeC(content))) {
							return Shell::filePutContentsAppend(fileNameOut, ";\r\n");
						};
					};
				};
			};
		};
		return false;
	};

	bool fileToCStringDirect(const char *fileNameIn, const char *fileNameOut) {
		String content;
		if (Shell::fileGetContents(fileNameIn, content)) {
			return Shell::filePutContents(fileNameOut, String::encodeC(content));
		};
		return false;
	};
};
