
FLAGS=-std=c++17 -Wall -Wpedantic -D_GNU_SOURCE  -lfltk -lfltk_images
COMPILER=g++

main:  BoardModel.o BoxModel.o main.cpp InterfaceGraphique.o  ControllerBoard.o  
	${COMPILER} -o jeu.exe main.cpp InterfaceGraphique.o BoardModel.o BoxModel.o ControllerBoard.o  ${FLAGS}

run:
	make main 

BoardModel.o: Model/BoardModel.cpp Model/BoardModel.hpp   Constants.hpp
	${COMPILER} -c Model/BoardModel.cpp ${FLAGS}

BoxModel.o: Model/BoxModel.cpp Model/BoxModel.hpp   Constants.hpp
	${COMPILER} -c Model/BoxModel.cpp ${FLAGS}


ControllerBoard.o: ControllerBoard.cpp ControllerBoard.hpp   Constants.hpp
	${COMPILER} -c ControllerBoard.cpp ${FLAGS}



InterfaceGraphique.o:  ControllerBoard.o InterfaceGraphique.cpp InterfaceGraphique.hpp Constants.hpp
	${COMPILER} -c InterfaceGraphique.cpp ${FLAGS}

clean :
	rm -f *.o




