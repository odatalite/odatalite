lib_LIBRARIES = libodata.a

libodata_a_SOURCES = \
    alloc.c \
    alloc.h \
    array.c \
    chars.c \
    chars.h \
    compare.c \
    compare.h \
    deserialize.c \
    destructors.c \
    destructors.h \
    format.c \
    format.h \
    getters.c \
    getters.h \
    jsonarray.c \
    jsonarray.h \
    json.h \
    jsonobject.c \
    jsonobject.h \
    jsonparser.c \
    jsonparser.h \
    name.h \
    object.c \
    odatacxx.h \
    odatacxxinlines.h \
    odata.h \
    odatamacros.h \
    outstream.c \
    outstream.h \
    pair.c \
    pair.h \
    providerentry.c \
    providerentry.h \
    providerentryprint.c \
    result.c \
    result.h \
    return.h \
    scope.c \
    scope.h \
    scratchbuf.h \
    serialize.c \
    serialize.h \
    setters.c \
    setters.h \
    types.c \
    types.h \
    uri.c \
    uri.h \
    uriparser.c \
    uriparser.h \
    queryoption.c \
    queryoption.h \
    csdl.h \
    csdl.c

include_HEADERS = odata.h odatacxx.h odatacxxinlines.h

INCLUDES = -I$(top_srcdir)/src

odataincludedir = $(includedir)/odata

#libodata_a_CFLAGS = -Winline

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/libodata.*
