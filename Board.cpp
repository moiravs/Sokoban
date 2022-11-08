#include "Board.hpp"

void Board::draw()
{
    for (auto &c : cells)
        c.draw();
}
void Board::mouseMove(Point mouseLoc)
{
    for (auto &c : cells)
        c.mouseMove(mouseLoc);
}
void Board::mouseClick(Point mouseLoc)
{
    for (auto &c : cells)
        c.mouseClick(mouseLoc);
}

void Board::keyPressed(int keyCode){
    return;
}

void Board::initialize(){
    return;
}