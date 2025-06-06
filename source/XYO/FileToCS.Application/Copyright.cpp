// File to CS
// Copyright (c) 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToCS.Application/Copyright.hpp>
#include <XYO/FileToCS.Application/Copyright.rh>

namespace XYO::FileToCS::Application::Copyright {

	static const char *copyright_ = XYO_FILETOCS_APPLICATION_COPYRIGHT;
	static const char *publisher_ = XYO_FILETOCS_APPLICATION_PUBLISHER;
	static const char *company_ = XYO_FILETOCS_APPLICATION_COMPANY;
	static const char *contact_ = XYO_FILETOCS_APPLICATION_CONTACT;

	const char *copyright() {
		return copyright_;
	};

	const char *publisher() {
		return publisher_;
	};

	const char *company() {
		return company_;
	};

	const char *contact() {
		return contact_;
	};

};
