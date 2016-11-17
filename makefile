all: report.pdf
report.pdf: report.tex kilder.bib
	latexmk -pdf
clean:
	latexmk -c
	rm *.bbl *.run.xml
read:
	evince report.pdf &
