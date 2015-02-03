bin_PROGRAMS = base64enc

INCLUDES = -I$(top_srcdir)/src

base64enc_SOURCES = base64enc.c

base64enc_LDADD = ../../base/libbase.a

install-exec-hook:
	rm -f $(DESTDIR)/$(bindir)/base64enc
