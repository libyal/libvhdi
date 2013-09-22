if HAVE_LOCAL_LIBFGUID
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@

noinst_LTLIBRARIES = libfguid.la

libfguid_la_SOURCES = \
	libfguid_definitions.h \
	libfguid_extern.h \
	libfguid_error.c libfguid_error.h \
	libfguid_identifier.c libfguid_identifier.h \
	libfguid_libcerror.h \
	libfguid_libcstring.h \
	libfguid_support.c libfguid_support.h \
	libfguid_types.h \
	libfguid_unused.h
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libfguid ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libfguid_la_SOURCES)

