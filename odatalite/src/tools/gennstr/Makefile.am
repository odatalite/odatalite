bin_PROGRAMS = gennstr

INCLUDES = -I$(top_srcdir)/src

gennstr_SOURCES = gennstr.c

gennstr_LDADD = ../../base/libbase.a

install-exec-hook:
	rm -f $(DESTDIR)/$(bindir)/gennstr
