#ifndef LOGICCELL_HPP
#define LOGICCELL_HPP

#include "BoxModel.hpp"
#include "Player.hpp"
#include "../Constants.hpp"
#include <iostream>


class LogicCell
{
private:
    size_t line, column;
    Box *box = nullptr;
    Player *player = nullptr;
    int color = FL_YELLOW;

protected:
public:
    enum cellType
    {
        Normal = EMPTY,
        Wall = WALL,
        Teleportation = TELEPORTATION,
        Box_final_pos = BOX_FINAL_POS,
    };
    cellType type;

    LogicCell(){};
    LogicCell(size_t line, size_t column, cellType type) : line{line}, column{column}, type{type}{} ;
    cellType getType()
    {
        return this->type;
    };
    int getX(){
        return this->column;
    }
    int getY(){
        return this->line;
    }
    bool isBoxBlocked()
    {
        if (this->box != nullptr)
        {
            return this->box->blocked;
        }
        return false;
    }
    void setColor(int color){
        this->color = color;
    }

    bool isComplete(){
        if (this->type == Box_final_pos){
            if (this->box !=nullptr){
                return (this->box->getColor() == this->color);
            }
            return false;
        }
        return true;
    }
    int getColor(){
        return this->color;
    }
    bool isBlocked(){
        if (this->type == WALL){
            return true;
        }
        else if (this->isBoxBlocked() == true){
            return true;
        }
        else {
            return false;
        }

    }
    void setBoxblocked()
    {
        if (this->box != nullptr)
            this->box->blocked = true;
        else
            puts("no box");
    }
    void setBox(Box *box)
    {
        this->box = box;
    }
    void setPlayer(Player *player)
    {
        this->player = player;
    }
    void setType(cellType type)
    {
        this->type = type;
    }
    bool hasBox()
    {
        if (this->box != nullptr)
        {
            return true;
        }
        return false;
    }
    Box *getBox()
    {
        if (this->box != nullptr)
        {
            return this->box;
        }
        else
        {
            std::cout << "error";
        }
    }
    bool hasPlayer()
    {
        if (this->player != nullptr)
        {
            return true;
        }
        return false;
    }
};
#endif