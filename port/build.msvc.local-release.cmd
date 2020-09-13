@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> local-release file-to-cs

goto cmdXDefined
:cmdX
%*
if errorlevel 1 goto cmdXError
goto :eof
:cmdXError
echo "Error: local-release"
exit 1
:cmdXDefined

set XYO_PATH_RELEASE=release

call :cmdX call port\build.msvc.cmd make
call :cmdX call port\build.msvc.cmd sign
call :cmdX call port\build.msvc.cmd install
call :cmdX call port\build.msvc.cmd install-release
call :cmdX xyo-cc file-to-cs --archive-release-sha512 --version-file=source/file-to-cs.version.ini
