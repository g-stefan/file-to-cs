// File to CS
// Copyright (c) 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILETOCS_DEPENDENCY_HPP
#define XYO_FILETOCS_DEPENDENCY_HPP

#ifndef XYO_SYSTEM_HPP
#	include <XYO/System.hpp>
#endif

// -- Export

#ifdef FILE_TO_CS_INTERNAL
#	ifndef XYO_FILETOCS_INTERNAL
#		define XYO_FILETOCS_INTERNAL
#	endif
#endif

#ifdef FILE_TO_CS_DLL_INTERNAL
#	ifndef XYO_FILETOCS_DLL_INTERNAL
#		define XYO_FILETOCS_DLL_INTERNAL
#	endif
#endif

#ifdef XYO_FILETOCS_DLL_INTERNAL
#	define XYO_FILETOCS_EXPORT XYO_PLATFORM_LIBRARY_EXPORT
#else
#	define XYO_FILETOCS_EXPORT XYO_PLATFORM_LIBRARY_IMPORT
#endif
#ifdef XYO_FILETOCS_LIBRARY
#	undef XYO_FILETOCS_EXPORT
#	define XYO_FILETOCS_EXPORT
#endif

namespace XYO::FileToCS {
	using namespace XYO::System;
};

#endif
