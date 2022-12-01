// File to CS
// Copyright (c) 2022 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2022 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToCS/Copyright.hpp>
#include <XYO/FileToCS/Copyright.rh>

namespace XYO::FileToCS::Copyright {

	static const char *copyright_ = XYO_FILETOCS_COPYRIGHT;
	static const char *publisher_ = XYO_FILETOCS_PUBLISHER;
	static const char *company_ = XYO_FILETOCS_COMPANY;
	static const char *contact_ = XYO_FILETOCS_CONTACT;
	static const char *fullCopyright_ = XYO_FILETOCS_FULL_COPYRIGHT;

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

	const char *fullCopyright() {
		return fullCopyright_;
	};

};
