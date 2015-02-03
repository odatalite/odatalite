lib_LIBRARIES = libclient.a

INCLUDES = -I$(top_srcdir)/src

libclient_a_SOURCES = \
    client.c \
    client.h

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/libclient.*
