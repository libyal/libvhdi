# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
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

am_pyvhdi_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
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

pyexec_LTLIBRARIES = pyvhdi.la

nodist_pyvhdi_la_SOURCES = $(BUILT_SOURCES)

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

pyvhdi_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pyvhdi_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyvhdi/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyvhdi*.[ch]

distclean: clean
	/bin/rm -f Makefile

