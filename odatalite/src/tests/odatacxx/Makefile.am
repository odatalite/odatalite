bin_PROGRAMS = testodatacxx

check_PROGRAMS = testodatacxx

TESTS = $(check_PROGRAMS)

INCLUDES = -I$(top_srcdir)/src

testodatacxx_SOURCES = testodatacxx.cpp

testodatacxx_LDADD = ../../odata/libodata.a ../../base/libbase.a

install-exec-hook:
	rm -f $(DESTDIR)/$(bindir)/testodatacxx
