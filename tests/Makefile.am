AM_CPPFLAGS = \
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
	@LIBVHDI_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYVHDI = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_vhdiinfo.sh \
	$(TESTS_PYVHDI)

check_SCRIPTS = \
	pyvhdi_test_file.py \
	pyvhdi_test_read.py \
	pyvhdi_test_support.py \
	test_library.sh \
	test_python_module.sh \
	test_runner.sh \
	test_vhdiinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vhdi_test_block_table \
	vhdi_test_data_block \
	vhdi_test_error \
	vhdi_test_file \
	vhdi_test_io_handle \
	vhdi_test_notify \
	vhdi_test_support

vhdi_test_block_table_SOURCES = \
	vhdi_test_block_table.c \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_block_table_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_data_block_SOURCES = \
	vhdi_test_data_block.c \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_data_block_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_error_SOURCES = \
	vhdi_test_error.c \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_unused.h

vhdi_test_error_LDADD = \
	../libvhdi/libvhdi.la

vhdi_test_file_SOURCES = \
	vhdi_test_file.c \
	vhdi_test_functions.c vhdi_test_functions.h \
	vhdi_test_getopt.c vhdi_test_getopt.h \
	vhdi_test_libbfio.h \
	vhdi_test_libcerror.h \
	vhdi_test_libclocale.h \
	vhdi_test_libcnotify.h \
	vhdi_test_libcpath.h \
	vhdi_test_libuna.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvhdi/libvhdi.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

vhdi_test_io_handle_SOURCES = \
	vhdi_test_io_handle.c \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_io_handle_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_notify_SOURCES = \
	vhdi_test_libbfio.h \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_notify.c \
	vhdi_test_unused.h

vhdi_test_notify_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_support_SOURCES = \
	vhdi_test_functions.c vhdi_test_functions.h \
	vhdi_test_getopt.c vhdi_test_getopt.h \
	vhdi_test_libbfio.h \
	vhdi_test_libcerror.h \
	vhdi_test_libclocale.h \
	vhdi_test_libcnotify.h \
	vhdi_test_libuna.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_support.c \
	vhdi_test_unused.h

vhdi_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

