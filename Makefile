
FLAGS=-std=c++17 -Wall -Wpedantic -D_GNU_SOURCE  -lfltk -lfltk_images -Wold-style-cast -Werror -fsanitize=address
COMPILER=g++

SOURCES=Model/BoardModel.cpp View/CellDisplay.cpp Model/LogicCell.cpp Controller/MainWindow.cpp Model/Teleportation.cpp

%.o: %.cpp %.hpp Constants.hpp
	${COMPILER} -c %.cpp ${FLAGS}

main:  LogicCell.o BoardModel.o main.cpp DisplayBoard.o  MainWindow.o Teleportation.o CellDisplay.o HelpWindow.o StartWindow.o
	${COMPILER} -o jeu main.cpp DisplayBoard.o BoardModel.o MainWindow.o  Teleportation.o CellDisplay.o LogicCell.o  HelpWindow.o StartWindow.o ${FLAGS}

run:
	make main 

BoardModel.o: Model/BoardModel.cpp Model/BoardModel.hpp Constants.hpp
	${COMPILER} -c Model/BoardModel.cpp ${FLAGS}

CellDisplay.o: View/CellDisplay.cpp View/CellDisplay.hpp Constants.hpp
	${COMPILER} -c View/CellDisplay.cpp ${FLAGS}

LogicCell.o: Model/LogicCell.cpp Model/LogicCell.hpp Constants.hpp
	${COMPILER} -c Model/LogicCell.cpp ${FLAGS}

DisplayBoard.o:  View/DisplayBoard.cpp View/DisplayBoard.hpp Constants.hpp
	${COMPILER} -c View/DisplayBoard.cpp ${FLAGS}



HelpWindow.o:  View/HelpWindow.cpp View/HelpWindow.hpp Constants.hpp
	${COMPILER} -c View/HelpWindow.cpp ${FLAGS}

StartWindow.o:  View/StartWindow.cpp View/StartWindow.hpp Constants.hpp
	${COMPILER} -c View/StartWindow.cpp ${FLAGS}

MainWindow.o:  Controller/MainWindow.cpp Controller/MainWindow.hpp Constants.hpp
	${COMPILER} -c Controller/MainWindow.cpp ${FLAGS}

Teleportation.o:  Model/Teleportation.cpp Model/Teleportation.hpp Constants.hpp
	${COMPILER} -c Model/Teleportation.cpp ${FLAGS}

clean :
	rm -f *.o
	rm jeu



