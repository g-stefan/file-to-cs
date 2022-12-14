// File to CS
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOCS_DEPENDENCY_HPP
#define XYO_FILETOCS_DEPENDENCY_HPP

#ifndef XYO_SYSTEM_HPP
#	include <XYO/System.hpp>
#endif

// -- Export

#ifndef XYO_FILETOCS_INTERNAL
#	ifdef FILE_TO_CS_INTERNAL
#		define XYO_FILETOCS_INTERNAL
#	endif
#endif

#ifdef XYO_FILETOCS_INTERNAL
#	define XYO_FILETOCS_EXPORT XYO_LIBRARY_EXPORT
#else
#	define XYO_FILETOCS_EXPORT XYO_LIBRARY_IMPORT
#endif

namespace XYO::FileToCS {
	using namespace XYO::System;
};

#endif
