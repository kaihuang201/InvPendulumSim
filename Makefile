CC = g++
CFLAGS = -std=c++11 

all: InvPendulumSim

InvPendulumSim: main.o InvPendulumEngine.o
	${CC} main.o InvPendulumEngine.o -o InvPendulumSim -pthread -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp InvPendulumEngine.o
	${CC} ${CFLAGS} -c main.cpp

InvPendulumEngine.o: InvPendulumEngine.h InvPendulumEngine.cpp
	${CC} ${CFLAGS} -c InvPendulumEngine.cpp

.PHONY: clean
clean:
	rm *.o InvPendulumSim
