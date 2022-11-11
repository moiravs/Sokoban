#include "Constantes.hpp"
struct Point
{
    int x, y;
};

class Rectangle
{
    Point center;
    int w, h;
    int type;
    Fl_Color fillColor, frameColor;

public:
    Rectangle(Point center, int w, int h, int type, Fl_Color frameColor = FL_BLACK,
              Fl_Color fillColor = FL_WHITE);
    void draw();
    void setFillColor(Fl_Color newFillColor);
    void setFrameColor(Fl_Color newFrameColor);
    bool contains(Point p);
};
class CellView
{
    Rectangle r;
    

public:
    CellView(Point center, int w, int h, int type);
    void draw();
};

class CellModel
{
private:
    Rectangle r;

public:
};
class CellController
{
private:
    bool on = false;
    Rectangle r;

public:
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
};