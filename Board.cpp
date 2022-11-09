#include "Board.hpp"

void Board::draw()
{
    for (auto &v : cells)
        for (auto &c: v)
            c.draw();
}
void Board::mouseMove(Point mouseLoc)
{
    for (auto &v : cells)
        for (auto &c: v)
            c.mouseMove(mouseLoc);
}
void Board::mouseClick(Point mouseLoc)
{
    for (auto &v : cells)
        for (auto &c : v)
            c.mouseClick(mouseLoc);
}

void Board::keyPressed(int keyCode){
    return;
}

void Board::initialize(){
    cells.clear();
    for (unsigned short x = 0; x < 10; x++){
        cells.push_back({});
        for (int y = 0; y < 10; y++){
            cells[x].push_back({{50*x+25, 50*y+25}, 40, 40});
        }
    }
    return;
}

void Board::clear(){
    return;
}