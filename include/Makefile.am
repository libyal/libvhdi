include_HEADERS = \
	libvhdi.h

pkginclude_HEADERS = \
	libvhdi/codepage.h \
	libvhdi/definitions.h \
	libvhdi/error.h \
	libvhdi/extern.h \
	libvhdi/features.h \
	libvhdi/types.h

EXTRA_DIST = \
	libvhdi.h.in \
	libvhdi/definitions.h.in \
	libvhdi/features.h.in \
	libvhdi/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libvhdi.h
	-rm -f libvhdi/definitions.h
	-rm -f libvhdi/features.h
	-rm -f libvhdi/types.h
	-rm -f Makefile

