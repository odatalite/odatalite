lib_LTLIBRARIES = librootprovider.la

librootprovider_la_SOURCES = \
    RootProvider.h \
    RootProvider.cpp

librootprovider_la_LDFLAGS = -shared -fPIC

INCLUDES = -I$(top_srcdir)/src

librootprovider_la_LINK = $(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(AM_CXXFLAGS) \
	$(CXXFLAGS) $(librootprovider_la_LDFLAGS) $(LDFLAGS) -o $@

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/librootprovider.*

