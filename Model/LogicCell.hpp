#include <iostream>

class LogicCell
{
private:
    size_t line, column;
protected:

public:
    enum cellType
    {
        Normal,
        Wall,
        Teleportation,
        Box_final_pos,
    };
    cellType type;
    LogicCell(){};
    LogicCell(size_t line, size_t column, cellType type): line{line}, column{column}, type{type} {};
    cellType getType();
    
};