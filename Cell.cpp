#include "Cell.hpp"

Rectangle::Rectangle(Point center, int w, int h, int type, Fl_Color frameColor,
                     Fl_Color fillColor) : center{center}, w{w}, h{h}, type{type}, fillColor{fillColor}, frameColor{frameColor} {}

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

Cell::Cell(Point center, int w, int h, int type) : r(center, w, h, type, FL_BLACK, FL_WHITE) {
    if (type==1){
        r.setFillColor(FL_BLUE);
    }
    else if(type==2){
        r.setFillColor(FL_GREEN);
    }
}
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
