#include "Cell.hpp"
class Canvas
{
    std::vector<Cell> cells;

public:
    Canvas();
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void keyPressed(int /*keyCode*/)
    {
        exit(0);
    }
};