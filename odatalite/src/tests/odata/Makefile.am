bin_PROGRAMS = testodata

check_PROGRAMS = testodata

EXTRA_DIST = providers.conf

AM_CPPFLAGS = -DTESTDIR="\"$(srcdir)\""

TESTS = $(check_PROGRAMS)

INCLUDES = -I$(top_srcdir)/src

testodata_SOURCES = testodata.c

testodata_LDADD = ../../odata/libodata.a ../../base/libbase.a

install-exec-hook:
	rm -f $(DESTDIR)/$(bindir)/testodata
