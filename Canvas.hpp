#include "Cell.hpp"
class Board
{
    std::vector<Cell> cells;

public:
    Board();
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void keyPressed(int /*keyCode*/)
    {
        exit(0);
    }
};