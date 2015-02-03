bin_PROGRAMS = base64dec

INCLUDES = -I$(top_srcdir)/src

base64dec_SOURCES = base64dec.c

base64dec_LDADD = ../../base/libbase.a

install-exec-hook:
	rm -f $(DESTDIR)/$(bindir)/base64dec
