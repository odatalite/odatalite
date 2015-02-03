bin_PROGRAMS = csdl2c

INCLUDES = -I$(top_srcdir)/src

csdl2c_SOURCES = csdl2c.c xml.c xml.h

csdl2c_LDADD = ../base/libbase.a

AM_LDFLAGS = -lexpat

#install-exec-hook:
#	rm -f $(DESTDIR)/$(bindir)/csdl2c
