//
// File to CS
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef FILE_TO_CS_COPYRIGHT_HPP
#define FILE_TO_CS_COPYRIGHT_HPP

#define FILE_TO_CS_COPYRIGHT            "Copyright (c) Grigore Stefan"
#define FILE_TO_CS_PUBLISHER            "Grigore Stefan"
#define FILE_TO_CS_COMPANY              FILE_TO_CS_PUBLISHER
#define FILE_TO_CS_CONTACT              "g_stefan@yahoo.com"
#define FILE_TO_CS_FULL_COPYRIGHT       FILE_TO_CS_COPYRIGHT " <" FILE_TO_CS_CONTACT ">"

#ifndef XYO_RC

namespace FileToCs {
	namespace Copyright {
		const char *copyright();
		const char *publisher();
		const char *company();
		const char *contact();
		const char *fullCopyright();
	};
};

#endif
#endif
