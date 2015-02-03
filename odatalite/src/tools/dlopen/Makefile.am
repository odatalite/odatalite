bin_PROGRAMS = dlopen

INCLUDES = -I$(top_srcdir)/src

dlopen_SOURCES = dlopen.c

dlopen_LDADD = ../../base/libbase.a -ldl

install-exec-hook:
	rm -f $(DESTDIR)/$(bindir)/dlopen
