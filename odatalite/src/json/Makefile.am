bin_PROGRAMS = json

INCLUDES = -I$(top_srcdir)/src

json_SOURCES = json.c

json_LDADD = ../odata/libodata.a ../base/libbase.a

install-exec-hook:
	rm -f $(DESTDIR)/$(bindir)/json

