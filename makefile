gpp = c++ -std=c++11 -O3 -Wall

ifeq (${USER},anders)
	parallel = -fopenmp
else
    parallel =
endif

latexsrc = report.tex latex/kilder.bib latex/analyticalonedim.tex latex/cranknicolson.tex latex/introduction.tex  latex/preamble.tex latex/analyticaltwodim.tex latex/discretisation.tex latex/vonneumann.tex latex/appendix.tex latex/eulertwodim.tex latex/onedimres.tex latex/backwardeuler.tex latex/forwardeuler.tex latex/physics.tex latex/twodimres.tex

all: report.pdf animation.gif
report.pdf: ${latexsrc} deltaxtest.plt twodim001.plt twodim01.plt
	latexmk -pdf report.tex
animation.gif: animate1d.py animation.dat
	python animate1d.py animation.dat
animation.dat: onedim_ui.x
	./onedim_ui.x animation.dat Crank_Nicolson 0.00001 0.3 0.01 300
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
twodim.x: twodim.cpp
	${gpp} ${parallel} -o twodim.x twodim.cpp
deltaxtest.plt: deltaxtest.gpi forward_Euler_0.1.dat analytic.dat
	gnuplot deltaxtest.gpi
analytic.dat: analytic.py
	python analytic.py
forward_Euler_0.1.dat: deltaxtest.sh onedim_ui.x
	./deltaxtest.sh
twodim001.plt: plottwodim.gpi twodim0010.00000000.dat
	gnuplot -e "filename='twodim001'" plottwodim.gpi
twodim0010.00000000.dat: twodim.x
	./twodim.x "twodim001" 0.00001 0.01 1000
twodim01.plt: plottwodim.gpi twodim010.00000000.dat
	gnuplot -e "filename='twodim01'" plottwodim.gpi
twodim010.00000000.dat: twodim.x
	./twodim.x "twodim01" 0.001 0.1 10
clean:
	latexmk -c
	rm *.dat *.plt
	rm *.bbl *.run.xml *.o *.x
	rm *.eps *-to.pdf *.tdo
edit:
	vim *.tex latex/*.tex makefile *.cpp *.h *.gpi *.sh *.py latex/*.bib
read:
	evince report.pdf &
