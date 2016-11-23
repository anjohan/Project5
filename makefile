gpp = g++ -std=c++11 -O3 -Wall

all: report.pdf
report.pdf: report.tex kilder.bib
	latexmk -pdf
onedimlib.o: onedimlib.cpp onedimlib.h
	${gpp} -c -fopenmp onedimlib.cpp
test.o: test.cpp
	${gpp} -c test.cpp
test.x: test.o onedimlib.o tridiagonalsolver.o
	${gpp} -fopenmp -o test.x test.o onedimlib.o tridiagonalsolver.o
tridiagonalsolver.o: tridiagonalsolver.cpp tridiagonalsolver.h
	${gpp} -c tridiagonalsolver.cpp
onedim_ui.o: onedim_ui.cpp
	${gpp} -c onedim_ui.cpp
onedim_ui.x: onedim_ui.o onedimlib.o tridiagonalsolver.o
	${gpp} -fopenmp -o onedim_ui.x onedim_ui.o onedimlib.o tridiagonalsolver.o
clean:
	latexmk -c
	rm *.dat
	rm *.bbl *.run.xml
edit:
	vim *.tex makefile *.cpp *.h *.bib
read:
	evince report.pdf &
