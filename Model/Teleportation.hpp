/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "LogicCell.hpp"

class Teleportation;

class Teleportation
{
    LogicCell *firstEnd;
    LogicCell *secondEnd;
    size_t line, column;

public:
    Teleportation(){};
    /**
     * @brief  Getter for the secondEnd of the teleportation
     * @retval
     */
    LogicCell *getSecondEnd();
    /**
     * @brief
     * @retval
     */
    LogicCell *getFirstEnd();
    std::tuple<int, int> getOtherEnd(int x, int y)
    {
        if (y == this->firstEnd->getY() && x == this->firstEnd->getX())
        {
            return {this->secondEnd->getY(), this->secondEnd->getX()};
        }
        else if (y == this->secondEnd->getY() && x == this->secondEnd->getX())
        {
            return {this->firstEnd->getY(), this->firstEnd->getX()};
        }
        else
        {
            return {-1, -1};
        }
    }
    void setFirstEnd(LogicCell *firstEnd)
    {
        this->firstEnd = firstEnd;
    }
    void setSecondEnd(LogicCell *secondEnd)
    {
        this->secondEnd = secondEnd;
    }
};