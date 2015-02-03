lib_LTLIBRARIES = libwidgetprovider.la

libwidgetprovider_la_SOURCES = \
    widgetprovider.c

libwidgetprovider_la_LDFLAGS = -shared -fPIC -L../../../base -lbase

INCLUDES = -I$(top_srcdir)/src

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/libwidgetprovider.*

