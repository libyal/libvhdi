AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	@PTHREAD_CPPFLAGS@ \
	@LIBVHDI_DLL_IMPORT@

if HAVE_PYTHON
TESTS_PYVHDI = \
	test_pyvhdi_open_close.sh \
	test_pyvhdi_seek.sh
endif

TESTS = \
	test_open_close.sh \
	test_seek.sh \
	test_read.sh \
	test_vhdiinfo.sh \
	$(TESTS_PYVHDI)

check_SCRIPTS = \
	pyvhdi_test_open_close.py \
	pyvhdi_test_seek.py \
	test_pyvhdi_open_close.sh \
	test_open_close.sh \
	test_pyvhdi_open_close.sh \
	test_pyvhdi_seek.sh \
	test_read.sh \
	test_runner.sh \
	test_seek.sh \
	test_vhdiinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vhdi_test_open_close \
	vhdi_test_read \
	vhdi_test_seek

vhdi_test_open_close_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libcstring.h \
	vhdi_test_libcthreads.h \
	vhdi_test_libvhdi.h \
	vhdi_test_open_close.c \
	vhdi_test_unused.h

vhdi_test_open_close_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

vhdi_test_read_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libcstring.h \
	vhdi_test_libcthreads.h \
	vhdi_test_libvhdi.h \
	vhdi_test_read.c \
	vhdi_test_unused.h

vhdi_test_read_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

vhdi_test_seek_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libcstring.h \
	vhdi_test_libcthreads.h \
	vhdi_test_libvhdi.h \
	vhdi_test_seek.c \
	vhdi_test_unused.h

vhdi_test_seek_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

