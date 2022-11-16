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
    int board_handle(int event)
    {
        if (Fl::event_key() == FL_Up)
        {
            boardi->move(boardi->player_x, boardi->player_y - 1);
        }
        else if (Fl::event_key() == FL_Down)
        {
            boardi->move(boardi->player_x, boardi->player_y + 1);
        }
        else if (Fl::event_key() == FL_Right)
        {
            boardi->move(boardi->player_x + 1, boardi->player_y);
        }
        else if (Fl::event_key() == FL_Left)
        {
            boardi->move(boardi->player_x - 1, boardi->player_y);
        }

        puts("hii");
        if (boardi->end_of_party())
        {
            std::cout << "youpi";
        }
        return 1;
    }
    void reset_handle()
    {
        std::string aer = this->boardi->readFileIntoString();
        this->boardi->createBoard(aer);
        puts("aeeaa");
    }
    void level_change(int choice)
    {
        std::cout << choice << std::endl;
        if (choice == -1){
            return;
        }
        if (choice == 0){
            this->boardi->filename = level1;}
        else if (choice==1)
            this->boardi->filename = level2;
        std::string buffer = this->boardi->readFileIntoString();
        this->boardi->createBoard(buffer);
    }
    // event inside -> inside a widget or not
};
#endif
