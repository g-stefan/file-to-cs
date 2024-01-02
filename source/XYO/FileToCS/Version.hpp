// File to CS
// Copyright (c) 2007-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOCS_VERSION_HPP
#define XYO_FILETOCS_VERSION_HPP

#ifndef XYO_FILETOCS_DEPENDENCY_HPP
#	include <XYO/FileToCS/Dependency.hpp>
#endif

namespace XYO::FileToCS::Version {

	XYO_FILETOCS_EXPORT const char *version();
	XYO_FILETOCS_EXPORT const char *build();
	XYO_FILETOCS_EXPORT const char *versionWithBuild();
	XYO_FILETOCS_EXPORT const char *datetime();

};

#endif
