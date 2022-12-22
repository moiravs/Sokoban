/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef LOGICCELL_HPP
#define LOGICCELL_HPP

#include "BoxModel.hpp"
#include "Player.hpp"
#include "../Constants.hpp"

class LogicCell
{
private:
    size_t line, column;
    Box *box = nullptr;
    Player *player = nullptr;
    int color = FL_YELLOW;
    int type;

protected:
public:
    LogicCell(){};
    LogicCell(size_t line, size_t column, int type) : line{line}, column{column}, type{type} {};
    int getType()
    {
        return this->type;
    };
    int getX()
    {
        return this->column;
    }
    int getY()
    {
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
    void setColor(int color)
    {
        this->color = color;
    }

    bool isComplete()
    {
        if (this->type == BOX_FINAL_POS)
        {
            if (this->box != nullptr)
            {
                return (this->box->color == this->color);
            }
            return false;
        }
        return true;
    }
    int getColor()
    {
        return this->color;
    }
    bool isBlocked()
    {
        if (this->type == WALL)
        {
            return true;
        }
        else if (this->isBoxBlocked() == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void setBoxblocked()
    {
        if (this->box != nullptr)
            this->box->blocked = true;
    }
    void setBox(Box *box)
    {
        this->box = box;
    }
    void setPlayer(Player *player)
    {
        this->player = player;
    }
    void setType(int type)
    {
        this->type = type;
    }
    bool hasBox()
    {
        if (this->box != nullptr)
            return true;
        return false;
    }
    Box *getBox()
    {
        return (this->box);
    }
    bool hasPlayer()
    {
        if (this->player != nullptr)
        {
            return true;
        }
        return false;
    }
    /*~LogicCell()
    {
        delete this->player;
        delete this->box;
        delete this;
    }*/
};
#endif