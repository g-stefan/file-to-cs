#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

ACTION=$1
if [ "$ACTION" = "" ]; then
	ACTION=make
fi

echo "- $BUILD_PROJECT > $ACTION"

cmdX(){
	if ! "$@" ; then
		echo "Error: $ACTION"
		exit 1
	fi
}

[ -d output ] || mkdir -p output
[ -d temp ] || mkdir -p temp

cmdX xyo-cc --mode=$ACTION @build/source/file-to-cs.compile
cmdX xyo-cc --mode=$ACTION @build/source/file-to-cs.library.compile
