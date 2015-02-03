lib_LTLIBRARIES = libgadgetprovider.la

libgadgetprovider_la_SOURCES = \
    gadgetprovider.c

libgadgetprovider_la_LDFLAGS = -shared -fPIC -L../../../base -lbase

INCLUDES = -I$(top_srcdir)/src

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/libgadgetprovider.*

