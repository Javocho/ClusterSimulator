OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

G++ = g++

all: program.exe

Cluster.o: Cluster.cc Cluster.hh
	$(G++) -c Cluster.cc $(OPCIONS) Cluster.hh

Procesador.o: Procesador.cc Procesador.hh
	$(G++) -c Procesador.cc $(OPCIONS) Procesador.hh

Area_espera.o: Area_espera.cc Area_espera.hh
	$(G++) -c Area_espera.cc $(OPCIONS) Area_espera.hh

Proceso.o: Proceso.cc Proceso.hh
	$(G++) -c Proceso.cc $(OPCIONS) Proceso.hh

program.o: program.cc
	$(G++) -c program.cc $(OPCIONS)

program.exe: program.o Cluster.o Procesador.o Area_espera.o Proceso.o
	$(G++) -o program.exe program.o Cluster.o Procesador.o Area_espera.o Proceso.o $(OPCIONS)
	
practica.tar:
	tar -cvf practica.tar Area_espera.hh Area_espera.cc Cluster.cc Cluster.hh Procesador.cc Procesador.hh Proceso.cc Proceso.hh program.cc Makefile html.zip 

clean:
	rm -f *.o
	rm -f *.exe
