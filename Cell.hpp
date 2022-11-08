#include "Constantes.hpp"
#include "Text.hpp"
struct Point
{
    int x, y;
};

class Rectangle
{
    Point center;
    int w, h;
    Fl_Color fillColor, frameColor;

public:
    Rectangle(Point center, int w, int h,
              Fl_Color frameColor = FL_BLACK,
              Fl_Color fillColor = FL_WHITE);
    void draw();
    void setFillColor(Fl_Color newFillColor);
    void setFrameColor(Fl_Color newFrameColor);
    bool contains(Point p);
};
class Cell
{
    Rectangle r;
    bool on = false;

public:
    Cell(Point center, int w, int h);
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
};