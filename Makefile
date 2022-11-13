
FLAGS=-std=c++17 -Wall -Wpedantic -D_GNU_SOURCE -Werror -lfltk -lfltk_images
COMPILER=g++

main:  main.cpp Player.o  Board.o 
	${COMPILER} -o jeu.exe main.cpp InterfaceGraphique.o Player.o  ${FLAGS}

run:
	make main 

Board.o: Board.hpp Board.cpp 
	${COMPILER} -c Board.cpp ${FLAGS}

Player.o: Player.cpp Player.hpp
	${COMPILER} -c Player.cpp ${FLAGS}

InterfaceGraphique.o: InterfaceGraphique.cpp InterfaceGraphique.hpp 
	${COMPILER} -c InterfaceGraphique.cpp ${FLAGS}

clean :
	rm -f *.o




