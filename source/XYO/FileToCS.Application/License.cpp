// File to CS
// Copyright (c) 2007-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToCS.Application/License.hpp>

namespace XYO::FileToCS::Application::License {

	std::string license() {
		return XYO::FileToCS::License::license();
	};

	std::string shortLicense() {
		return XYO::FileToCS::License::shortLicense();
	};

};
