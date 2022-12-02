
FLAGS=-std=c++17 -Wall -Wpedantic -D_GNU_SOURCE  -lfltk -lfltk_images
COMPILER=g++

main:  BoardModel.o BoxModel.o main.cpp DisplayBoard.o  MainWindow.o ControllerBoard.o  
	${COMPILER} -o jeu.exe main.cpp DisplayBoard.o MainWindow.o BoardModel.o BoxModel.o ControllerBoard.o  ${FLAGS}

run:
	make main 

BoardModel.o: Model/BoardModel.cpp Model/BoardModel.hpp Constants.hpp
	${COMPILER} -c Model/BoardModel.cpp ${FLAGS}

BoxModel.o: Model/BoxModel.cpp Model/BoxModel.hpp Constants.hpp
	${COMPILER} -c Model/BoxModel.cpp ${FLAGS}

ControllerBoard.o: Controller/ControllerBoard.cpp Controller/ControllerBoard.hpp Constants.hpp
	${COMPILER} -c Controller/ControllerBoard.cpp ${FLAGS}

DisplayBoard.o:  View/DisplayBoard.cpp View/DisplayBoard.hpp Constants.hpp
	${COMPILER} -c View/DisplayBoard.cpp ${FLAGS}

MainWindow.o:  View/MainWindow.cpp View/MainWindow.hpp Constants.hpp
	${COMPILER} -c View/MainWindow.cpp ${FLAGS}

clean :
	rm -f *.o




