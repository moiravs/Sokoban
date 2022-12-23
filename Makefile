
FLAGS=-std=c++17 -Wall -Wpedantic -D_GNU_SOURCE  -lfltk -lfltk_images
COMPILER=g++

main:  LogicCell.o BoardModel.o BoxModel.o main.cpp DisplayBoard.o  MainWindow.o Teleportation.o CellDisplay.o
	${COMPILER} -o jeu main.cpp DisplayBoard.o MainWindow.o BoardModel.o BoxModel.o Teleportation.o CellDisplay.o LogicCell.o ${FLAGS}

run:
	make main 

BoardModel.o: Model/BoardModel.cpp Model/BoardModel.hpp Constants.hpp
	${COMPILER} -c Model/BoardModel.cpp ${FLAGS}

BoxModel.o: Model/BoxModel.cpp Model/BoxModel.hpp Constants.hpp
	${COMPILER} -c Model/BoxModel.cpp ${FLAGS}

CellDisplay.o: View/CellDisplay.cpp View/CellDisplay.hpp Constants.hpp
	${COMPILER} -c View/CellDisplay.cpp ${FLAGS}

LogicCell.o: Model/LogicCell.cpp Model/LogicCell.hpp Constants.hpp
	${COMPILER} -c Model/LogicCell.cpp ${FLAGS}

DisplayBoard.o:  View/DisplayBoard.cpp View/DisplayBoard.hpp Constants.hpp
	${COMPILER} -c View/DisplayBoard.cpp ${FLAGS}

MainWindow.o:  Controller/MainWindow.cpp Controller/MainWindow.hpp Constants.hpp
	${COMPILER} -c Controller/MainWindow.cpp ${FLAGS}

Teleportation.o:  Model/Teleportation.cpp Model/Teleportation.hpp Constants.hpp
	${COMPILER} -c Model/Teleportation.cpp ${FLAGS}

clean :
	rm -f *.o
	rm jeu



