gpp = c++ -std=c++11 -O3 -Wall
ifeq (${USER},anders)
	parallel = -fopenmp
else
    parallel =
endif

all: report.pdf
report.pdf: report.tex kilder.bib deltaxtest.plt
	latexmk -pdf
onedimlib.o: onedimlib.cpp onedimlib.h
	${gpp} -c ${parallel} onedimlib.cpp
test.o: test.cpp
	${gpp} -c test.cpp
test.x: test.o onedimlib.o tridiagonalsolver.o
	${gpp} ${parallel} -o test.x test.o onedimlib.o tridiagonalsolver.o
tridiagonalsolver.o: tridiagonalsolver.cpp tridiagonalsolver.h
	${gpp} -c tridiagonalsolver.cpp
onedim_ui.o: onedim_ui.cpp
	${gpp} -c onedim_ui.cpp
onedim_ui.x: onedim_ui.o onedimlib.o tridiagonalsolver.o
	${gpp} ${parallel} -o onedim_ui.x onedim_ui.o onedimlib.o tridiagonalsolver.o
deltaxtest.plt: deltaxtest.gpi forward_Euler_0.1.dat analytic.dat
	gnuplot deltaxtest.gpi
analytic.dat: analytic.py
	python analytic.py
forward_Euler_0.1.dat: deltaxtest.sh onedim_ui.x
	./deltaxtest.sh
clean:
	latexmk -c
	rm *.dat
	rm *.bbl *.run.xml *.o *.x
	rm *.eps *-to.pdf
edit:
	vim *.tex makefile *.cpp *.h *.gpi *.sh *.py *.bib
read:
	evince report.pdf &
