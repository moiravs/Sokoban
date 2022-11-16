#include "Constants.hpp"
#include "Board.hpp"
#include "InterfaceGraphique.hpp"
class ControllerBoard : Fl_Box
{
private:
    std::shared_ptr<Board> boardi;

public:
    ControllerBoard(std::shared_ptr<Board> boardi) : Fl_Box(0,0,500,500)
    {
        this->boardi = boardi;
        DisplayBoard *board = new DisplayBoard(boardi);
        board->show();
    };
    //event inside -> inside a widget or not
};
