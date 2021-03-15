@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> sign file-to-cs

pushd output
for /r %%i in (*.exe) do call grigore-stefan.sign "File to C/C++ Source" "%%i"
popd
