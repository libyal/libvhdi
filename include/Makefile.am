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
	/bin/rm -f libvhdi.h
	/bin/rm -f libvhdi/definitions.h
	/bin/rm -f libvhdi/features.h
	/bin/rm -f libvhdi/types.h
	/bin/rm -f Makefile

