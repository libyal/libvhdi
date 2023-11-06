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
	libvhdi_block_allocation_table.c libvhdi_block_allocation_table.h \
	libvhdi_block_descriptor.c libvhdi_block_descriptor.h \
	libvhdi_checksum.c libvhdi_checksum.h \
	libvhdi_codepage.h \
	libvhdi_debug.c libvhdi_debug.h \
	libvhdi_definitions.h \
	libvhdi_dynamic_disk_header.c libvhdi_dynamic_disk_header.h \
	libvhdi_error.c libvhdi_error.h \
	libvhdi_extern.h \
	libvhdi_file.c libvhdi_file.h \
	libvhdi_file_footer.c libvhdi_file_footer.h \
	libvhdi_file_information.c libvhdi_file_information.h \
	libvhdi_i18n.c libvhdi_i18n.h \
	libvhdi_image_header.c libvhdi_image_header.h \
	libvhdi_io_handle.c libvhdi_io_handle.h \
	libvhdi_libbfio.h \
	libvhdi_libcdata.h \
	libvhdi_libcerror.h \
	libvhdi_libclocale.h \
	libvhdi_libcnotify.h \
	libvhdi_libcthreads.h \
	libvhdi_libfcache.h \
	libvhdi_libfdata.h \
	libvhdi_libfguid.h \
	libvhdi_libuna.h \
	libvhdi_metadata_item_identifier.c libvhdi_metadata_item_identifier.h \
	libvhdi_metadata_table.c libvhdi_metadata_table.h \
	libvhdi_metadata_table_entry.c libvhdi_metadata_table_entry.h \
	libvhdi_metadata_table_header.c libvhdi_metadata_table_header.h \
	libvhdi_metadata_values.c libvhdi_metadata_values.h \
	libvhdi_notify.c libvhdi_notify.h \
	libvhdi_parent_locator.c libvhdi_parent_locator.h \
	libvhdi_parent_locator_entry.c libvhdi_parent_locator_entry.h \
	libvhdi_parent_locator_header.c libvhdi_parent_locator_header.h \
	libvhdi_region_table.c libvhdi_region_table.h \
	libvhdi_region_table_entry.c libvhdi_region_table_entry.h \
	libvhdi_region_table_header.c libvhdi_region_table_header.h \
	libvhdi_region_type_identifier.c libvhdi_region_type_identifier.h \
	libvhdi_sector_range_descriptor.c libvhdi_sector_range_descriptor.h \
	libvhdi_support.c libvhdi_support.h \
	libvhdi_types.h \
	libvhdi_unused.h \
	vhdi_dynamic_disk_header.h \
	vhdi_file_footer.h \
	vhdi_file_information.h \
	vhdi_image_header.h \
	vhdi_metadata_table.h \
	vhdi_parent_locator.h \
	vhdi_region_table.h

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
	-rm -f libvhdi_definitions.h
	-rm -f libvhdi.rc
	-rm -f Makefile

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libvhdi ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libvhdi_la_SOURCES)

