#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libvhdi/.libs/libvhdi.1.dylib" ] && [ -f ./pyvhdi/.libs/pyvhdi.so ]
then
    install_name_tool -change /usr/local/lib/libvhdi.1.dylib "${PWD}/libvhdi/.libs/libvhdi.1.dylib" ./pyvhdi/.libs/pyvhdi.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

