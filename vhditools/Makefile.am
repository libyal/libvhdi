AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	@LIBFUSE_CPPFLAGS@ \
	@LIBVHDI_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	vhdiinfo \
	vhdimount

vhdiinfo_SOURCES = \
	byte_size_string.c byte_size_string.h \
	info_handle.c info_handle.h \
	vhdiinfo.c \
	vhditools_getopt.c vhditools_getopt.h \
	vhditools_i18n.h \
	vhditools_libbfio.h \
	vhditools_libcdata.h \
	vhditools_libcerror.h \
	vhditools_libclocale.h \
	vhditools_libcnotify.h \
	vhditools_libfguid.h \
	vhditools_libvhdi.h \
	vhditools_libuna.h \
	vhditools_output.c vhditools_output.h \
	vhditools_signal.c vhditools_signal.h \
	vhditools_unused.h

vhdiinfo_LDADD = \
	@LIBFGUID_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

vhdimount_SOURCES = \
	mount_dokan.c mount_dokan.h \
	mount_file_entry.c mount_file_entry.h \
	mount_file_system.c mount_file_system.h \
	mount_fuse.c mount_fuse.h \
	mount_handle.c mount_handle.h \
	vhdimount.c \
	vhditools_getopt.c vhditools_getopt.h \
	vhditools_i18n.h \
	vhditools_libbfio.h \
	vhditools_libcdata.h \
	vhditools_libcerror.h \
	vhditools_libclocale.h \
	vhditools_libcnotify.h \
	vhditools_libcpath.h \
	vhditools_libvhdi.h \
	vhditools_libuna.h \
	vhditools_output.c vhditools_output.h \
	vhditools_signal.c vhditools_signal.h \
	vhditools_unused.h

vhdimount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

splint-local:
	@echo "Running splint on vhdiinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vhdiinfo_SOURCES)
	@echo "Running splint on vhdimount ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vhdimount_SOURCES)

