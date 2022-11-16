#ifndef CONTROLLERBOARD_HPP
#define CONTROLLERBOARD_HPP

#include "Constants.hpp"
#include "Board.hpp"
class ControllerBoard
{
private:
    std::shared_ptr<Board> boardi;

public:
    ControllerBoard(){}
    ControllerBoard(std::shared_ptr<Board> boardi) {
        this->boardi = boardi;
    };
    int key_handle(int event){
        boardi->move(4,2);
        puts("hii");
        return 1;
    }
    //event inside -> inside a widget or not
};
#endif
