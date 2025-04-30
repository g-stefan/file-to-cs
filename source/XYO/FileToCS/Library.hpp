// File to CS
// Copyright (c) 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOCS_LIBRARY_HPP
#define XYO_FILETOCS_LIBRARY_HPP

#ifndef XYO_FILETOCS_DEPENDENCY_HPP
#	include <XYO/FileToCS/Dependency.hpp>
#endif

namespace XYO::FileToCS {

	XYO_FILETOCS_EXPORT bool fileToCpp(const char *stringName, const char *fileNameIn, const char *fileNameOut, bool append, bool isString);
	XYO_FILETOCS_EXPORT bool fileToCString(const char *stringName, const char *fileNameIn, const char *fileNameOut);
	XYO_FILETOCS_EXPORT bool fileToCStringDirect(const char *fileNameIn, const char *fileNameOut);

};

#endif
