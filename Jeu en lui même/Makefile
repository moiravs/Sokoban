
FLAGS=-std=c++17 -Wall -Wpedantic -D_GNU_SOURCE -Werror -lfltk
COMPILER=g++

main: Constantes.hpp MainWindow.o main.cpp Board.o Cell.o Wall.o Player.o Board.o
	${COMPILER} -o jeu.exe Constantes.hpp ${FLAGS}

run:
	make main 

MainWindow.o:MainWindow.cpp MainWindow.hpp
	${COMPILER} -c MainWindow.cpp ${FLAGS}

Cell.o: Cell.cpp Cell.hpp
	${COMPILER} -c Cell.cpp ${FLAGS}

Board.o: Board.cpp Board.hpp Player.o
	${COMPILER} -c Board.cpp ${FLAGS}

clean :
	rm -f *.o

#Player.o: Player.cpp Player.hpp
#	${COMPILER} -c Player.cpp ${FLAGS}


#Wall.o: Wall.cpp Wall.hpp
#	${COMPILER} -c Wall.cpp ${FLAGS}

