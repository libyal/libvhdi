#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libvhdi/.libs/libvhdi.1.dylib && test -f ./pyvhdi/.libs/pyvhdi.so;
then
	install_name_tool -change /usr/local/lib/libvhdi.1.dylib ${PWD}/libvhdi/.libs/libvhdi.1.dylib ./pyvhdi/.libs/pyvhdi.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

