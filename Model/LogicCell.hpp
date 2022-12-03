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
        Normal = EMPTY,
        Wall = WALL,
        Teleportation = TELEPORTATION,
        Box_final_pos = BOX_FINAL_POS,
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