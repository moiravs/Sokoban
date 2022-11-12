#include "Player.hpp"
#include "InterfaceGraphique.hpp"
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
#include "Board.cpp"
#include <memory>

int main(int argc, char const *argv[])
{
    Fl::scheme("gtk+");
    auto b = std::make_shared<Board>();
    //DisplayBoard db{b};
    //ControlBoard controller{b};
    MainWindow window;
    window.show();
    Board board;
    std::string file = "Niveaux/niveau1.txt";
    std::string buffer = board.readFileIntoString(file);
    std::cout << buffer << std::endl;
    board.createBoard(buffer);
    board.move(4, 4);
    return Fl::run();
}
