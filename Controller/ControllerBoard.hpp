#ifndef CONTROLLERBOARD_HPP
#define CONTROLLERBOARD_HPP

#include "../Constants.hpp"
#include "../Model/BoardModel.hpp"

class ControllerBoard
{
private:
    std::shared_ptr<BoardModel> boardModel;

public:
    ControllerBoard() {}
    ControllerBoard(std::shared_ptr<BoardModel> boardModel)
    {
        this->boardModel = boardModel;
    };
    int board_handle(int event);
    void move_to(int x, int y);
};

#endif
