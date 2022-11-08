#include "Constantes.hpp"

#include "Cell.hpp"
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

Rectangle::Rectangle(Point center, int w, int h,
                     Fl_Color frameColor,
                     Fl_Color fillColor) : center{center}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor} {}

void Rectangle::draw()
{
    fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, fillColor);
    fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
}

void Rectangle::setFillColor(Fl_Color newFillColor)
{
    fillColor = newFillColor;
}

void Rectangle::setFrameColor(Fl_Color newFrameColor)
{
    frameColor = newFrameColor;
}

bool Rectangle::contains(Point p)
{
    return p.x >= center.x - w / 2 &&
           p.x < center.x + w / 2 &&
           p.y >= center.y - h / 2 &&
           p.y < center.y + h / 2;
}

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

Cell::Cell(Point center, int w, int h) : r(center, w, h, FL_BLACK, FL_WHITE) {}
void Cell::draw()
{
    r.draw();
}
void Cell::mouseMove(Point mouseLoc)
{
    if (r.contains(mouseLoc))
    {
        r.setFrameColor(FL_RED);
    }
    else
    {
        r.setFrameColor(FL_BLACK);
    }
}
void Cell::mouseClick(Point mouseLoc)
{
    if (r.contains(mouseLoc))
    {
        on = !on;
        if (on)
            r.setFillColor(FL_YELLOW);
        else
            r.setFillColor(FL_WHITE);
    }
}
