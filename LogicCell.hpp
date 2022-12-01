#include <iostream>

class LogicCell
{
private:
    size_t line, column;
protected:
    enum cellType {Normal, Teleportation};
    cellType type;
public:
    LogicCell(size_t line, size_t column, cellType type): line{line}, column{column}, type{type} {};
    cellType getType();
    
};