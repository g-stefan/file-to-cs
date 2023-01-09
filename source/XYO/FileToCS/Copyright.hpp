// File to CS
// Copyright (c) 2007-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOCS_COPYRIGHT_HPP
#define XYO_FILETOCS_COPYRIGHT_HPP

#ifndef XYO_FILETOCS_DEPENDENCY_HPP
#	include <XYO/FileToCS/Dependency.hpp>
#endif

namespace XYO::FileToCS::Copyright {
	const char *copyright();
	const char *publisher();
	const char *company();
	const char *contact();
};

#endif
