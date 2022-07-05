all:icon compile link run
icon:
	windres icon.rc -O coff -o my.res
compile:
	g++ -Isrc/include -Isrc/game -c main.cpp

link:
	g++ main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system

run:
	./main