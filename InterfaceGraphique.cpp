#include "InterfaceGraphique.hpp"

void Rectangle::draw()
{

    if (type == PLAYER)
    {
        Fl_Image *hihi = personnage;
        hihi->draw(center.x - w / 2, center.y - h / 2, w, h);
        // fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_BLUE);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, FL_BLUE);
    }
    else if (type == BOX)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_GREEN);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
    else if (type == EMPTY)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_RED);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
    else if (type == WALL)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_BLACK);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
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

Rectangle::Rectangle(Point center, int type, int w, int h,
                     Fl_Color frameColor,
                     Fl_Color fillColor) : center{center}, type{type}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor}
{
    this->personnage = new Fl_JPEG_Image("Textures/Test.jpeg");
}

Cell::Cell(Point center, int type, int w, int h) : r(center, type, w, h, FL_BLACK, FL_WHITE) {}

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

void DisplayBoard::draw()
{
    for (auto &c : cells)
        c.draw();
}

void DisplayBoard::printBoard()
{
    for (size_t i = 0; i < boardmodel->getMatrix().size(); i++)
    {
        for (size_t j = 0; j < boardmodel->getMatrix()[0].size(); j++)
        {
            std::cout << boardmodel->getMatrix()[i][j] << " ";
        }
        std::cout << "\n";
    }
}
