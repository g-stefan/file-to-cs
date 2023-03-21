// File to CS
// Copyright (c) 2007-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToCS/Copyright.hpp>
#include <XYO/FileToCS/Copyright.rh>

namespace XYO::FileToCS::Copyright {

	static const char *copyright_ = XYO_FILETOCS_COPYRIGHT;
	static const char *publisher_ = XYO_FILETOCS_PUBLISHER;
	static const char *company_ = XYO_FILETOCS_COMPANY;
	static const char *contact_ = XYO_FILETOCS_CONTACT;

	std::string copyright() {
		return copyright_;
	};

	std::string publisher() {
		return publisher_;
	};

	std::string company() {
		return company_;
	};

	std::string contact() {
		return contact_;
	};

};
