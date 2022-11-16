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
        if (Fl::event_key() == FL_Up)
        {
            boardi->move(boardi->player_x, boardi->player_y -1);
        }
        else if (Fl::event_key() == FL_Down)
        {
            boardi->move(boardi->player_x, boardi->player_y + 1);
        }
        else if (Fl::event_key() == FL_Right)
        {
            boardi->move(boardi->player_x +1, boardi->player_y);
        }
        else if (Fl::event_key() == FL_Left)
        {
            boardi->move(boardi->player_x - 1, boardi->player_y);
        }
        
        puts("hii");
        return 1;
    }
    //event inside -> inside a widget or not
};
#endif
