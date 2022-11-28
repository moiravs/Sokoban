#include <iostream>

class LogicCell
{
    size_t line, column;
    enum cellType {Empty, Correct, Box, LightBox, Wall};
    cellType type;
public:
    LogicCell(size_t line, size_t column, cellType type): line{line}, column{column}, type{type} {};
    cellType getType();
    
};