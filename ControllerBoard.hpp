#ifndef CONTROLLERBOARD_HPP
#define CONTROLLERBOARD_HPP

#include "Constants.hpp"
#include "Board.hpp"
class ControllerBoard
{
private:
    std::shared_ptr<Board> shared_board;

public:
    ControllerBoard() {}
    ControllerBoard(std::shared_ptr<Board> boardi)
    {
        this->shared_board = boardi;
    };
    int board_handle(int event);
    void reset_handle();
    void level_change(int choice);
    
};

#endif
