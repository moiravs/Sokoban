#ifndef BOX_CPP
#define BOX_CPP
#include "Box.hpp"


void Box::setX(int x)
{
    this->x = x;
}
void Box::setY(int y)
{
    this->y = y;
}
int Box::getX()
{
    return (this->x);
}
int Box::getY()
{
    return (this->y);
}




bool Box::operator==(const Box &box) const
{
return x == box.x && y == box.y;

}
#endif