lib_LIBRARIES = libbase.a

libbase_a_SOURCES = \
    addr.h \
    alloc.h \
    array.h \
    auth.h \
    base64.h \
    buf.h \
    chars.h \
    cleanup.h \
    datetime.h \
    dump.h \
    env.h \
    err.h \
    file.h \
    format.h \
    getopt.h \
    http.h \
    iprintf.h \
    log.h \
    pam.h \
    parse.h \
    path.h \
    pidfile.h \
    plugininfo.h \
    process.h \
    ptrarray.h \
    role.h \
    roundpow2.h \
    selector.h \
    shlib.h \
    sock.h \
    str.h \
    user.h \
    addr.c \
    addrclient.c \
    alloc.c \
    allocprint.c \
    array.c \
    auth.c \
    authclient.c \
    authserver.c \
    base64dec.c \
    base64enc.c \
    buf.c \
    chars.c \
    cleanup.c \
    datetime.c \
    datetimetimestamp.c \
    dump.c \
    env.c \
    err.c \
    file.c \
    format.c \
    getopt.c \
    http.c \
    httpclient.c \
    httpdump.c \
    httpserver.c \
    iprintf.c \
    log.c \
    pam.c \
    parse.c \
    path.c \
    pathdump.c \
    pathjoin.c \
    pathsplit.c \
    pidfile.c \
    plugininfo.c \
    process.c \
    ptrarray.c \
    role.c \
    roledump.c \
    roundpow2.c \
    selector.c \
    shlib.c \
    sock.c \
    socklisten.c \
    sockpeercreds.c \
    str.c \
    strhex.c \
    strint.c \
    strbool.c \
    strlcat.c \
    strlcpy.c \
    user.c \
    find.c \
    find.h \
    html.c \
    html.h \
    conffile.h \
    conffile.c \
    httpstatuscodes.c \
    httpstatuscodes.h

INCLUDES = -I$(top_srcdir)/src

baseincludedir = $(includedir)/base

install-exec-hook:
	rm -f $(DESTDIR)/$(libdir)/libbase.*

size:
	size *.o | sort -n
