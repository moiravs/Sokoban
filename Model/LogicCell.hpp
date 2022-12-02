#ifndef LOGICCELL_HPP
#define LOGICCELL_HPP



#include <iostream>

class LogicCell
{
private:
    size_t line, column;
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
    LogicCell(size_t line, size_t column, cellType type): line{line}, column{column}, type{type} {};
    cellType getType(){
        return this->type;
    };
    
};
#endif