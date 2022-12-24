/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "LogicCell.hpp"

bool LogicCell::hasBox()
{
    if (this->box != nullptr)
        return true;
    return false;
}
bool LogicCell::hasPlayer()
{
    if (this->player != nullptr)
        return true;
    return false;
}
bool LogicCell::isBlocked()
{
    if ((this->box != nullptr))
        return this->box->blocked;
    if ((this->type == WALL))
        return true;
    return false;
}
void LogicCell::setBoxblocked(bool blocked)
{
    if (this->box != nullptr)
        this->box->blocked = blocked;
}

bool LogicCell::isComplete()
{
    if (this->type == BOX_FINAL_POS)
    {
        if (this->box != nullptr)
            return (this->box->color == this->color);
        return false;
    }
    return true;
}
LogicCell::~LogicCell()
{
    delete this->player;
    delete this->box;
    delete this;
}