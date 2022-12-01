#include "LogicCell.hpp"

class Box
{
    int x;
    int y;
    bool blocked;
public:
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
};