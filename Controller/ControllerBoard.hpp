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
    void custom_handle();
    int board_handle(int event);
    void reset_handle();
    void saveminpas();
    void level_change(int choice);
};

#endif
