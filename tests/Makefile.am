AUTOMAKE_OPTIONS = subdir-objects

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
	test_tools.sh \
	test_vhdiinfo.sh \
	$(TESTS_PYVHDI)

check_SCRIPTS = \
	pyvhdi_test_file.py \
	pyvhdi_test_support.py \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh \
	test_vhdiinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vhdi_test_block_allocation_table \
	vhdi_test_block_descriptor \
	vhdi_test_checksum \
	vhdi_test_dynamic_disk_header \
	vhdi_test_error \
	vhdi_test_file \
	vhdi_test_file_footer \
	vhdi_test_file_information \
	vhdi_test_image_header \
	vhdi_test_io_handle \
	vhdi_test_metadata_table \
	vhdi_test_metadata_table_entry \
	vhdi_test_metadata_table_header \
	vhdi_test_metadata_values \
	vhdi_test_notify \
	vhdi_test_parent_locator \
	vhdi_test_parent_locator_entry \
	vhdi_test_parent_locator_header \
	vhdi_test_region_table \
	vhdi_test_region_table_entry \
	vhdi_test_region_table_header \
	vhdi_test_sector_range_descriptor \
	vhdi_test_support \
	vhdi_test_tools_info_handle \
	vhdi_test_tools_output \
	vhdi_test_tools_signal

vhdi_test_block_allocation_table_SOURCES = \
	vhdi_test_block_allocation_table.c \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_block_allocation_table_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_block_descriptor_SOURCES = \
	vhdi_test_block_descriptor.c \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_block_descriptor_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_checksum_SOURCES = \
	vhdi_test_checksum.c \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_checksum_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_dynamic_disk_header_SOURCES = \
	vhdi_test_dynamic_disk_header.c \
	vhdi_test_functions.c vhdi_test_functions.h \
	vhdi_test_libbfio.h \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_dynamic_disk_header_LDADD = \
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

vhdi_test_file_footer_SOURCES = \
	vhdi_test_file_footer.c \
	vhdi_test_functions.c vhdi_test_functions.h \
	vhdi_test_libbfio.h \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_file_footer_LDADD = \
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

vhdi_test_file_information_SOURCES = \
	vhdi_test_file_information.c \
	vhdi_test_functions.c vhdi_test_functions.h \
	vhdi_test_libbfio.h \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_file_information_LDADD = \
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

vhdi_test_image_header_SOURCES = \
	vhdi_test_functions.c vhdi_test_functions.h \
	vhdi_test_image_header.c \
	vhdi_test_libbfio.h \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_unused.h

vhdi_test_image_header_LDADD = \
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

vhdi_test_metadata_table_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_metadata_table.c \
	vhdi_test_unused.h

vhdi_test_metadata_table_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_metadata_table_entry_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_metadata_table_entry.c \
	vhdi_test_unused.h

vhdi_test_metadata_table_entry_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_metadata_table_header_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_metadata_table_header.c \
	vhdi_test_unused.h

vhdi_test_metadata_table_header_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_metadata_values_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_metadata_values.c \
	vhdi_test_unused.h

vhdi_test_metadata_values_LDADD = \
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

vhdi_test_parent_locator_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_parent_locator.c \
	vhdi_test_unused.h

vhdi_test_parent_locator_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_parent_locator_entry_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_parent_locator_entry.c \
	vhdi_test_unused.h

vhdi_test_parent_locator_entry_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_parent_locator_header_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_parent_locator_header.c \
	vhdi_test_unused.h

vhdi_test_parent_locator_header_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_region_table_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_region_table.c \
	vhdi_test_unused.h

vhdi_test_region_table_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_region_table_entry_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_region_table_entry.c \
	vhdi_test_unused.h

vhdi_test_region_table_entry_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_region_table_header_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_region_table_header.c \
	vhdi_test_unused.h

vhdi_test_region_table_header_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_sector_range_descriptor_SOURCES = \
	vhdi_test_libcerror.h \
	vhdi_test_libvhdi.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_sector_range_descriptor.c \
	vhdi_test_unused.h

vhdi_test_sector_range_descriptor_LDADD = \
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

vhdi_test_tools_info_handle_SOURCES = \
	../vhditools/byte_size_string.c ../vhditools/byte_size_string.h \
	../vhditools/info_handle.c ../vhditools/info_handle.h \
	vhdi_test_libcerror.h \
	vhdi_test_macros.h \
	vhdi_test_memory.c vhdi_test_memory.h \
	vhdi_test_tools_info_handle.c \
	vhdi_test_unused.h

vhdi_test_tools_info_handle_LDADD = \
	@LIBFGUID_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_tools_output_SOURCES = \
	../vhditools/vhditools_output.c ../vhditools/vhditools_output.h \
	vhdi_test_libcerror.h \
	vhdi_test_macros.h \
	vhdi_test_tools_output.c \
	vhdi_test_unused.h

vhdi_test_tools_output_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

vhdi_test_tools_signal_SOURCES = \
	../vhditools/vhditools_signal.c ../vhditools/vhditools_signal.h \
	vhdi_test_libcerror.h \
	vhdi_test_macros.h \
	vhdi_test_tools_signal.c \
	vhdi_test_unused.h

vhdi_test_tools_signal_LDADD = \
	../libvhdi/libvhdi.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

