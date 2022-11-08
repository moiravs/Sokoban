#include "Board.hpp"

Board::Board()
{
    for (int i = 0; i < 100; i++)
        cells.push_back(Cell{Point{50 * (i % 10) + 25, 50 * (i / 10) + 25}, 40, 40});
    // You could also write:
    //  cells.push_back({Point{50*(i%10)+25, 50*(i/10)+25}, 40, 40});
    //  cells.push_back({{50*(i%10)+25,50*(i/10)+25},40,40});
}
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