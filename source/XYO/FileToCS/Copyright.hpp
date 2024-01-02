// File to CS
// Copyright (c) 2007-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOCS_COPYRIGHT_HPP
#define XYO_FILETOCS_COPYRIGHT_HPP

#ifndef XYO_FILETOCS_DEPENDENCY_HPP
#	include <XYO/FileToCS/Dependency.hpp>
#endif

namespace XYO::FileToCS::Copyright {
	XYO_FILETOCS_EXPORT const char *copyright();
	XYO_FILETOCS_EXPORT const char *publisher();
	XYO_FILETOCS_EXPORT const char *company();
	XYO_FILETOCS_EXPORT const char *contact();
};

#endif
