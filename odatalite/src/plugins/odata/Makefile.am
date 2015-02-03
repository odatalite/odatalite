lib_LIBRARIES = libodataplugin.a

libodataplugin_a_SOURCES = \
    odataplugin.c \
    odataplugin.h \
    options.h \
    providers.c \
    providers.h \
    webpage.c \
    webpage.h \
    scope.c \
    scope.h \
    post.c \
    post.h

INCLUDES = -I$(top_srcdir)/src

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/libheapprovider.*

#AM_CPPFLAGS=-DSUPPORT_ODATA_3_0
