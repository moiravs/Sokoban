#include "CellDisplay.hpp"

PlayerDisplay::PlayerDisplay(Point center, int w, int h)
{
    this->personnage = new Fl_JPEG_Image(imageplayer.c_str());
    this->center = center;
    this->w = w;
    this->h = h;
}

void PlayerDisplay::draw()
{
    Fl_Image *hihi = this->personnage;
    hihi->draw(center.x - w / 2, center.y - h / 2, w, h);
    fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, FL_BLUE);
}

Cell::Cell(Point center, int type, int w, int h, int color) : center{center}, type{type}, w{w}, h{h}, color{color}
{
    this->wall = new Fl_PNG_Image(imagewall.c_str());
    if (type == PLAYER)
    {
        PlayerDisplay *player = new PlayerDisplay(center, w, h);
        this->personnage = player;
    }
}

bool Cell::contains(Point p) 
{
    return p.x >= center.x - w / 2 && p.x < center.x + w / 2 &&
           p.y >= center.y - h / 2 && p.y < center.y + h / 2;
}

void Cell::draw()
{

    if (type == PLAYER)
    {
        this->personnage->draw();
    }
    else if (type == BOX_FINAL_POS)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, this->color);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, FL_WHITE);
    }
    else
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, this->color);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, FL_BLACK);
    }
}

bool Cell::mouseClick(Point mouseLoc)
{
    if ((center.x - w / 2 < mouseLoc.x) && (mouseLoc.x < w + center.x - w / 2) && (center.y - h / 2 < mouseLoc.y) && (mouseLoc.y < h + center.y - h / 2))
        return true;
    return false;
}