//
// File to CS
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef FILE_TO_CS_VERSION_HPP
#define FILE_TO_CS_VERSION_HPP

#define FILE_TO_CS_VERSION_ABCD                $VERSION_ABCD
#define FILE_TO_CS_VERSION_STR                 "$VERSION_VERSION"
#define FILE_TO_CS_VERSION_STR_BUILD           "$VERSION_BUILD"
#define FILE_TO_CS_VERSION_STR_DATETIME        "$VERSION_DATETIME"

#ifndef XYO_RC

namespace FileToCS {
	namespace Version {
		const char *version();
		const char *build();
		const char *versionWithBuild();
		const char *datetime();
	};
};

#endif
#endif

