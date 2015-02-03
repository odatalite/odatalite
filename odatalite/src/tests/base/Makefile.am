bin_PROGRAMS = testbase

check_PROGRAMS = testbase

EXTRA_DIST = \
    $(srcdir)/phitplugins.conf \
    $(srcdir)/FindFile/a/b/c/README \
    $(srcdir)/roles.conf \
    $(srcdir)/rolesbad.conf \
    $(srcdir)/myfile.conf \
    $(srcdir)/conffile.conf

AM_CPPFLAGS = -DTESTDIR="\"$(srcdir)\""

INCLUDES = -I$(top_srcdir)/src

TESTS = $(check_PROGRAMS)

testbase_SOURCES = testbase.c

testbase_LDADD = ../../base/libbase.a

install-exec-hook:
	rm -f $(DESTDIR)/$(bindir)/testbase
