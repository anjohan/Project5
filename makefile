all: report.pdf
report.pdf: report.tex kilder.bib
	latexmk -pdf
clean:
	latexmk -c
	rm *.bbl *.run.xml
edit:
	vim *.tex *.bib
read:
	evince report.pdf &
