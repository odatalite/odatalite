bin_PROGRAMS = phitd

INCLUDES = -I$(top_srcdir)/src

phitd_SOURCES = \
    connection.c \
    connection.h \
    context.c \
    context.h \
    contextoptions.h \
    defaultplugin.c \
    defaultplugin.h \
    disp.c \
    disp.h \
    help.c \
    help.h \
    listener.c \
    listener.h \
    options.h \
    plugin.c \
    plugin.h \
    server.c \
    webpage.c \
    webpage.h

phitd_LDADD = \
    ../plugins/odata/libodataplugin.a \
    ../odata/libodata.a \
    ../base/libbase.a \
    -lpam 

cg:
	cachegrind ./phitd -i

vg:
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./phitd -i

size:
	size ./phitd
