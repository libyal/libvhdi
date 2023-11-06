if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBVHDI_DLL_IMPORT@

pyexec_LTLIBRARIES = pyvhdi.la

pyvhdi_la_SOURCES = \
	pyvhdi.c pyvhdi.h \
	pyvhdi_disk_types.c pyvhdi_disk_types.h \
	pyvhdi_error.c pyvhdi_error.h \
	pyvhdi_file.c pyvhdi_file.h \
	pyvhdi_file_object_io_handle.c pyvhdi_file_object_io_handle.h \
	pyvhdi_guid.c pyvhdi_guid.h \
	pyvhdi_integer.c pyvhdi_integer.h \
	pyvhdi_libbfio.h \
	pyvhdi_libcerror.h \
	pyvhdi_libclocale.h \
	pyvhdi_libfguid.h \
	pyvhdi_libvhdi.h \
	pyvhdi_python.h \
	pyvhdi_unused.h

pyvhdi_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libvhdi/libvhdi.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFGUID_LIBADD@

pyvhdi_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyvhdi_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

