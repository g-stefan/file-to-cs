// File to CS
// Copyright (c) 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2007-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileToCS.Application/Version.hpp>
#include <XYO/FileToCS.Application/Version.rh>

namespace XYO::FileToCS::Application::Version {

	static const char *version_ = XYO_FILETOCS_APPLICATION_VERSION_STR;
	static const char *build_ = XYO_FILETOCS_APPLICATION_VERSION_STR_BUILD;
	static const char *versionWithBuild_ = XYO_FILETOCS_APPLICATION_VERSION_STR_WITH_BUILD;
	static const char *datetime_ = XYO_FILETOCS_APPLICATION_VERSION_STR_DATETIME;

	const char *version() {
		return version_;
	};
	const char *build() {
		return build_;
	};
	const char *versionWithBuild() {
		return versionWithBuild_;
	};
	const char *datetime() {
		return datetime_;
	};

};
