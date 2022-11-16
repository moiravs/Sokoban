#ifndef CONTROLLERBOARD_HPP
#define CONTROLLERBOARD_HPP

#include "Constants.hpp"
#include "Board.hpp"
class ControllerBoard
{
private:
    std::shared_ptr<Board> boardi;

public:
    ControllerBoard() {}
    ControllerBoard(std::shared_ptr<Board> boardi)
    {
        this->boardi = boardi;
    };
    int board_handle(int event);
    void reset_handle();
    void level_change(int choice);
    
};

#endif
