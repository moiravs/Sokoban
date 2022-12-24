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
    int getType() { return this->type; };
    int getX() { return this->column; }
    int getY() { return this->line; }
    void setColor(int color) { this->color = color; }
    void setBoxblocked(bool blocked);
    void setBox(Box *box) { this->box = box; }
    void setPlayer(Player *player) { this->player = player; }
    void setType(int type) { this->type = type; }
    int getColor() { return this->color; }
    Box *getBox() { return (this->box); }
    /**
     * @brief  Check if there is a box on the box final pos
     * @retval return true if there is a box of the same color on the final box
     * pos, true if the logicCell is not a final box pos, else otherwise
     */
    bool isComplete();
    /**
     * @brief  Check if the box on the LogicCell is blocked or if the LogicCell is a wall
     * @retval Return true if the box on the LogicCell is blocked or if the LogicCell is a wall.
     */
    bool isBlocked();
    /**
     * @brief  Check if the LogicCell has a box
     * @retval Returns true if the LogicCell has a box
     */
    bool hasBox();
    /**
     * @brief  Check if the LogicCell has a player
     * @retval Returns true if the LogicCell has a player
     */
    bool hasPlayer();
    ~LogicCell();
};
#endif