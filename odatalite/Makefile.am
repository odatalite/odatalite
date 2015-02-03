## Run automake to generate Makefile.in
.PHONY: objsizefile
AUTOMAKE_OPTIONS = gnu
SUBDIRS = . src

EXTRA_DIST = \
    ./etc/phit/phitd.conf \
    ./etc/phit/phitd.conf.install \
    ./etc/phit/plugins.conf \
    ./etc/phit/plugins.conf.install \
    ./etc/phit/providers.conf \
    ./etc/phit/providers.conf.install \
    ./etc/phit/roles.conf \
    ./etc/phit/roles.conf.install \
    ./var/log/ \
    ./var/run/ \
    ./share/phit/preamble.html \
    ./share/phit/odata.html \
    ./share/phit/postamble.html \
    ./share/phit/background.gif \
    ./src/base/phit.pam

install-data-hook:
	mkdir -p $(DESTDIR)/$(localstatedir)/run
	mkdir -p $(DESTDIR)/$(localstatedir)/phitauth
	mkdir -p $(DESTDIR)/$(localstatedir)/log
	mkdir -p $(DESTDIR)/$(sysconfdir)/phit
	mkdir -p $(DESTDIR)/$(datarootdir)/phit
	cp $(top_srcdir)/etc/phit/phitd.conf.install $(DESTDIR)/$(sysconfdir)/phit/phitd.conf
	cp $(top_srcdir)/etc/phit/plugins.conf.install $(DESTDIR)/$(sysconfdir)/phit/plugins.conf
	cp $(top_srcdir)/etc/phit/providers.conf.install $(DESTDIR)/$(sysconfdir)/phit/providers.conf
	cp $(top_srcdir)/etc/phit/roles.conf.install $(DESTDIR)/$(sysconfdir)/phit/roles.conf
	cp $(top_srcdir)/share/phit/preamble.html $(DESTDIR)/$(datarootdir)/phit/preamble.html
	cp $(top_srcdir)/share/phit/odata.html $(DESTDIR)/$(datarootdir)/phit/odata.html
	cp $(top_srcdir)/share/phit/postamble.html $(DESTDIR)/$(datarootdir)/phit/postamble.html
	cp $(top_srcdir)/share/phit/background.gif $(DESTDIR)/$(datarootdir)/phit/background.gif

install-exec-hook:
	mkdir -p $(DESTDIR)/$(bindir)

uninstall-hook:
	rm -f $(DESTDIR)/$(sysconfdir)/phit/phitd.conf
	rm -f $(DESTDIR)/$(sysconfdir)/phit/plugins.conf
	rm -f $(DESTDIR)/$(sysconfdir)/phit/providers.conf
	rm -f $(DESTDIR)/$(sysconfdir)/phit/roles.conf
	rm -f $(DESTDIR)/$(datarootdir)/phit/preamble.html
	rm -f $(DESTDIR)/$(datarootdir)/phit/odata.html
	rm -f $(DESTDIR)/$(datarootdir)/phit/postamble.html
	rm -f $(DESTDIR)/$(datarootdir)/phit/background.gif

dist-hook:
	rm -rf `find $(distdir) -type d -name CVS`

sources:
	@ find . -name '*.h' -print > SOURCES
	@ find . -name '*.c' -print >> SOURCES
	@ find . -name '*.cpp' -print >> SOURCES
	@ echo "Created ./SOURCES"

objsizefile:
	rm -f objsize.txt
	ls ./src/base/*.o >> objsize.txt
	ls ./src/odata/*.o >> objsize.txt
	ls ./src/plugins/odata/*.o >> objsize.txt
	ls ./src/server/*.o >> objsize.txt

objsize: objsizefile
	@ size `cat objsize.txt` | grep -v "text.*data.*bss.*dec" | sort -k 4  -n
	@ rm -f objsize.txt

