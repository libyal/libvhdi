AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@LIBVHDI_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	vhdiinfo \
	vhdimount

vhdiinfo_SOURCES = \
	info_handle.c info_handle.h \
	vhdiinfo.c \
	vhdioutput.c vhdioutput.h \
	vhditools_libbfio.h \
	vhditools_libcdata.h \
	vhditools_libcerror.h \
	vhditools_libclocale.h \
	vhditools_libcnotify.h \
	vhditools_libcstring.h \
	vhditools_libcsystem.h \
	vhditools_libfguid.h \
	vhditools_libvhdi.h \
	vhditools_libuna.h

vhdiinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	../libvhdi/libvhdi.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

vhdimount_SOURCES = \
	mount_handle.c mount_handle.h \
	vhdimount.c \
	vhdioutput.c vhdioutput.h \
	vhditools_libbfio.h \
	vhditools_libcdata.h \
	vhditools_libcerror.h \
	vhditools_libclocale.h \
	vhditools_libcnotify.h \
	vhditools_libcpath.h \
	vhditools_libcstring.h \
	vhditools_libcsystem.h \
	vhditools_libvhdi.h \
	vhditools_libuna.h

vhdimount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	../libvhdi/libvhdi.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on vhdiinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vhdiinfo_SOURCES)
	@echo "Running splint on vhdimount ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vhdimount_SOURCES)

