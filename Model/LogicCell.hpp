#ifndef LOGICCELL_HPP
#define LOGICCELL_HPP

#include "BoxModel.hpp"
#include <iostream>

class LogicCell
{
private:
    size_t line, column;
    Box *box = nullptr;
    Player *player = nullptr;

protected:
public:
    enum cellType
    {
        Normal = 0,
        Wall = 3,
        Teleportation = 4,
        Box_final_pos = 6,
    };
    cellType type;

    LogicCell(){};
    LogicCell(size_t line, size_t column, cellType type) : line{line}, column{column}, type{type} {};
    cellType getType()
    {
        return this->type;
    };
    bool isBoxBlocked()
    {
        if (this->box != nullptr)
        {
            return this->box->blocked;
        }
        return false;
    }
    void setBox(Box *box)
    {
        this->box = box;
    }
    void setPlayer(Player *player)
    {
        this->player = player;
    }
    bool hasBox()
    {
        if (this->box != nullptr)
        {
            return true;
        }
        return false;
    }
};
#endif