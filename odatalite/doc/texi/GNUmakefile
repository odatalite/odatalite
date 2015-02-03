all:
	texi2dvi odatalite.texi
	dvipdf odatalite.dvi odatalite.pdf
	makeinfo odatalite.texi
	makeinfo --no-split --html odatalite.texi
	$(MAKE) clean

clean:
	rm -f *.aux *.cp *.dvi *.fn *.ky *.log *.pg *.toc *.tp *.vr
