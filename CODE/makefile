all: main.c ARRBSoption.o ARRoption.o BSToption.o HASHoption.o LINKLISToption.o
	gcc main.c ARRBSoption.o ARRoption.o BSToption.o HASHoption.o LINKLISToption.o -o main

ARRBSoption.o: ARRBSoption.c ARRBSoption.h
	gcc -c ARRBSoption.c -o ARRBSoption.o

ARRoption.o: ARRoption.c ARRoption.h
	gcc -c ARRoption.c -o ARRoption.o

BSToption.o: BSToption.c BSToption.h
	gcc -c BSToption.c -o BSToption.o

HASHoption.o: HASHoption.c HASHoption.h
	gcc -c HASHoption.c -o HASHoption.o

LINKLISToption.o: LINKLISToption.c LINKLISToption.h
	gcc -c LINKLISToption.c -o LINKLISToption.o

clean: 
	rm -f ARRBSoption.o ARRoption.o BSToption.o HASHoption.o LINKLISToption.o main
