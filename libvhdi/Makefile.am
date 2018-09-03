AM_CPPFLAGS = \
	-DLOCALEDIR=\"$(datadir)/locale\" \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
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
	@PTHREAD_CPPFLAGS@ \
	@LIBVHDI_DLL_EXPORT@

lib_LTLIBRARIES = libvhdi.la

libvhdi_la_SOURCES = \
	libvhdi.c \
	libvhdi_block_table.c libvhdi_block_table.h \
	libvhdi_codepage.h \
	libvhdi_data_block.c libvhdi_data_block.h \
	libvhdi_debug.c libvhdi_debug.h \
	libvhdi_definitions.h \
	libvhdi_error.c libvhdi_error.h \
	libvhdi_extern.h \
	libvhdi_file.c libvhdi_file.h \
	libvhdi_i18n.c libvhdi_i18n.h \
	libvhdi_io_handle.c libvhdi_io_handle.h \
	libvhdi_libbfio.h \
	libvhdi_libcerror.h \
	libvhdi_libclocale.h \
	libvhdi_libcnotify.h \
	libvhdi_libcthreads.h \
	libvhdi_libfcache.h \
	libvhdi_libfdata.h \
	libvhdi_libfguid.h \
	libvhdi_libuna.h \
	libvhdi_notify.c libvhdi_notify.h \
	libvhdi_support.c libvhdi_support.h \
	libvhdi_types.h \
	libvhdi_unused.h \
	vhdi_dynamic_disk_header.h \
	vhdi_file_footer.h

libvhdi_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@PTHREAD_LIBADD@

libvhdi_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libvhdi_definitions.h.in \
	libvhdi.rc \
	libvhdi.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libvhdi_definitions.h
	/bin/rm -f libvhdi.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libvhdi ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libvhdi_la_SOURCES)

