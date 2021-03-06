//
// File to CS
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef FILE_TO_CS_VERSION_HPP
#define FILE_TO_CS_VERSION_HPP

#define FILE_TO_CS_VERSION_ABCD                1,5,0,8
#define FILE_TO_CS_VERSION_STR                 "1.5.0"
#define FILE_TO_CS_VERSION_STR_BUILD           "8"
#define FILE_TO_CS_VERSION_STR_DATETIME        "2021-03-15 12:30:20"

#ifndef XYO_RC

namespace FileToCs {
	namespace Version {
		const char *version();
		const char *build();
		const char *versionWithBuild();
		const char *datetime();
	};
};

#endif
#endif

