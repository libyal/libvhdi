MSVSCPP_FILES = \
	dokan/dokan.vcproj \
	libbfio/libbfio.vcproj \
	libcdata/libcdata.vcproj \
	libcerror/libcerror.vcproj \
	libcfile/libcfile.vcproj \
	libclocale/libclocale.vcproj \
	libcnotify/libcnotify.vcproj \
	libcpath/libcpath.vcproj \
	libcsplit/libcsplit.vcproj \
	libcstring/libcstring.vcproj \
	libcsystem/libcsystem.vcproj \
	libcthreads/libcthreads.vcproj \
	libfcache/libfcache.vcproj \
	libfdata/libfdata.vcproj \
	libfguid/libfguid.vcproj \
	libuna/libuna.vcproj \
	libvhdi/libvhdi.vcproj \
	pyvhdi/pyvhdi.vcproj \
	vhdi_test_open_close/vhdi_test_open_close.vcproj \
	vhdi_test_read/vhdi_test_read.vcproj \
	vhdi_test_seek/vhdi_test_seek.vcproj \
	vhdiinfo/vhdiinfo.vcproj \
	vhdimount/vhdimount.vcproj \
	libvhdi.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

