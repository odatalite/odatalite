lib_LTLIBRARIES = libfrogprovider.la

libfrogprovider_la_SOURCES = \
    FrogProvider.cpp \
    FrogProvider.h \
    strings.h

libfrogprovider_la_LDFLAGS = -shared -fPIC

INCLUDES = -I$(top_srcdir)/src

libfrogprovider_la_LINK = $(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(AM_CXXFLAGS) \
	$(CXXFLAGS) $(libfrogprovider_la_LDFLAGS) $(LDFLAGS) -o $@

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/libfrogprovider.*

