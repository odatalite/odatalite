lib_LTLIBRARIES = libheapprovider.la

libheapprovider_la_SOURCES = \
    HeapProvider.cpp \
    HeapProvider.h

libheapprovider_la_LDFLAGS = -shared -fPIC

INCLUDES = -I$(top_srcdir)/src

libheapprovider_la_LINK = $(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(AM_CXXFLAGS) \
	$(CXXFLAGS) $(libheapprovider_la_LDFLAGS) $(LDFLAGS) -o $@

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/libheapprovider.*

