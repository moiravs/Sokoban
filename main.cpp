

#include "Board.hpp"
#include "InterfaceGraphique.hpp"


#include "Player.hpp"

#include <iostream>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include <array>
#include <memory>


int main(int argc, char const *argv[])
{
    Fl::scheme("gtk+");
    auto b = std::make_shared<Board>();
    std::string file = "Niveaux/niveau1.txt";
    std::string buffer = b->readFileIntoString(file);
    std::cout << buffer << std::endl;
    b->createBoard(buffer);
    b->move(4, 2);
    DisplayBoard db{b};
    // DisplayBoard db;
    // ControlBoard controller{b};
    MainWindow window(db);
    window.show();
    //db.printBoard();
    return Fl::run();
}
