
FLAGS=-std=c++17 -Wall -Wpedantic -D_GNU_SOURCE -Werror -lfltk -lfltk_images
COMPILER=g++

main:  Board.o main.cpp InterfaceGraphique.o  Player.o 
	${COMPILER} -o jeu.exe main.cpp InterfaceGraphique.o Board.o Player.o  ${FLAGS}

run:
	make main 

Board.o: Board.cpp Board.hpp 
	${COMPILER} -c Board.cpp ${FLAGS}

Player.o: Player.cpp Player.hpp
	${COMPILER} -c Player.cpp ${FLAGS}

InterfaceGraphique.o: InterfaceGraphique.cpp InterfaceGraphique.hpp
	${COMPILER} -c InterfaceGraphique.cpp ${FLAGS}

clean :
	rm -f *.o




