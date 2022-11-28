
FLAGS=-std=c++17 -Wall -Wpedantic -D_GNU_SOURCE  -lfltk -lfltk_images
COMPILER=g++

main:  Board.o main.cpp InterfaceGraphique.o  ControllerBoard.o  
	${COMPILER} -o jeu.exe main.cpp InterfaceGraphique.o Board.o ControllerBoard.o  ${FLAGS}

run:
	make main 

Board.o: Board.cpp Board.hpp   Constants.hpp
	${COMPILER} -c Board.cpp ${FLAGS}

ControllerBoard.o: ControllerBoard.cpp ControllerBoard.hpp   Constants.hpp
	${COMPILER} -c ControllerBoard.cpp ${FLAGS}



InterfaceGraphique.o:  ControllerBoard.o InterfaceGraphique.cpp InterfaceGraphique.hpp Constants.hpp
	${COMPILER} -c InterfaceGraphique.cpp ${FLAGS}

clean :
	rm -f *.o




