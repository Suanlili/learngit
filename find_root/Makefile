root :
	gcc -o roots src/roots.c -IGSL/include -LGSL/lib -lgsl -lgslcblas
	mv roots ./bin
report :
	xelatex ./doc/report.tex
	mv report.pdf report.aux report.log doc
	echo NOTE, pdf file is in ./doc
