/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef LOGICCELL_HPP
#define LOGICCELL_HPP

#include "../Constants.hpp"

struct Player
{
    int x;
    int y;
};
struct Box
{
    int color = FL_WHITE;
    bool light = false;
    bool blocked = false;
};
class LogicCell
{
private:
    size_t line, column;
    Box *box = nullptr;
    Player *player = nullptr;
    int color = FL_WHITE;
    int type;

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
            return this->box->blocked;
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
                return (this->box->color == this->color);
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
        if ((this->type == WALL) || this->isBoxBlocked())
            return true;
        return false;
    }
    void setBoxblocked(bool blocked)
    {
        if (this->box != nullptr)
            this->box->blocked = blocked;
    }
    void setBox(Box *box)
    {
        this->box = box;
    }
    void setPlayer(Player *player) { this->player = player; }
    void setType(int type) { this->type = type; }
    bool hasBox()
    {
        if (this->box != nullptr)
            return true;
        return false;
    }
    Box *getBox() { return (this->box); }
    bool hasPlayer()
    {
        if (this->player != nullptr)
            return true;
        return false;
    }
    ~LogicCell()
    {
        delete this->player;
        delete this->box;
        delete this;
    }
};
#endif