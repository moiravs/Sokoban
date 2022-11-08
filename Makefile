
FLAGS=-std=c++17 -Wall -Wpedantic -D_GNU_SOURCE -Werror -lfltk
COMPILER=g++

main: Constantes.hpp MainWindow.o main.cpp Player.o Canvas.o Wall.o Cell.o Board.o
	${COMPILER} -o jeu Constantes.o MainWindow.o main.cpp Canvas.o Player.o Wall.o Cell.o Board.o ${FLAGS}

run:
	make main 


MainWindow.o:MainWindow.cpp MainWindow.hpp
	${COMPILER} -c MainWindow.cpp ${FLAGS}

Cell.o: Cell.cpp Cell.hpp
	${COMPILER} -c Cell.cpp ${FLAGS}

Canvas.o: Canvas.cpp Canvas.hpp Player.o
	${COMPILER} -c Canvas.cpp ${FLAGS}

Player.o: Player.cpp Player.hpp
	${COMPILER} -c Player.cpp ${FLAGS}

Board.o: Board.cpp Board.hpp
	${COMPILER} -c Board.cpp ${FLAGS}

Wall.o: Wall.cpp Wall.hpp
	${COMPILER} -c Wall.cpp ${FLAGS}

