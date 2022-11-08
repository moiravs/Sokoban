#include "Constantes.hpp"
#include "Cell.hpp"
#include "Text.hpp"

class Canvas
{
    Text textGameOver{"Game Over", {250, 250}, 90, fl_rgb_color(255, 0, 255)};
    Text textYouWin{"You Win!", {250, 250}, 90, FL_GREEN};
    std::vector<std::vector<Cell>> cells;
    std::vector<Cell *> neighbors(int x, int y);
    int neighborBombCount(int x, int y);
    void initialize();

public:
    Canvas()
    {
        initialize();
    }
    bool bombExposed();
    bool solved();
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void keyPressed(int keyCode);
};