lib_LTLIBRARIES = libmetadataprovider.la

libmetadataprovider_la_SOURCES = \
    metadataprovider.c \
    ServiceRoot.c

libmetadataprovider_la_LDFLAGS = -shared -fPIC -L../../../base -lbase

INCLUDES = -I$(top_srcdir)/src

gen:
	../../../csdl2c/csdl2c ../../../RedfishSchema/ServiceRoot.0.9.2.metadata

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/libmetadataprovider.*

