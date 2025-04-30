// File to CS
// Copyright (c) 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToCS/License.hpp>
#include <XYO/FileToCS/Copyright.hpp>

namespace XYO::FileToCS::License {

	std::string license() {
		std::string retV;
		retV += Platform::License::licenseMITHeader();
		retV += Copyright::copyright();
		retV += "\r\n";
		retV += Platform::License::licenseMITContent();
		return retV;
	};

	std::string shortLicense() {
		std::string retV;
		retV += Copyright::copyright();
		retV += "\r\n";
		retV += Platform::License::licenseMITShort();
		return retV;
	};

};
