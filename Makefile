all: compile link run

compile:
	g++ -Isrc/include -c main.cpp

link:
	g++ main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system

run:
	./main.exe