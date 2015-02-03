all-local: $(SHLIB)
	mkdir -p $(top_srcdir)/lib
	chmod +w $(top_srcdir)/lib
	rm -f $(SHLIBTARGET)
	rm -f $(SHLIBTARGET)
	ln -s $(SHLIB) $(SHLIBTARGET)

clean-local:
	rm -f $(SHLIBTARGET)
