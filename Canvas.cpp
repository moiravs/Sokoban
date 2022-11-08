#include "Canvas.hpp"

Canvas::Canvas()
{
    for (int i = 0; i < 100; i++)
        cells.push_back(Cell{Point{50 * (i % 10) + 25, 50 * (i / 10) + 25}, 40, 40});
    // You could also write:
    //  cells.push_back({Point{50*(i%10)+25, 50*(i/10)+25}, 40, 40});
    //  cells.push_back({{50*(i%10)+25,50*(i/10)+25},40,40});
}
void Canvas::draw()
{
    for (auto &c : cells)
        c.draw();
}
void Canvas::mouseMove(Point mouseLoc)
{
    for (auto &c : cells)
        c.mouseMove(mouseLoc);
}
void Canvas::mouseClick(Point mouseLoc)
{
    for (auto &c : cells)
        c.mouseClick(mouseLoc);
}