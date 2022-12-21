

#include "Model/BoardModel.hpp"
#include "View/DisplayBoard.hpp"
#include "View/MainWindow.hpp"


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
    std::string file = level1;
    auto boardModel = std::make_shared<BoardModel>(file);
    std::string buffer = boardModel->readFileIntoString();
    boardModel->createBoard(buffer);
    MainWindow window(boardModel);
    window.show();
    StartWindow start;
    return Fl::run();
}
