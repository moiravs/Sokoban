/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "CellDisplay.hpp"

Cell::Cell(Point center, int type, int w, int h, int color) : center{center}, type{type}, w{w}, h{h}, color{color}
{
    if (type == PLAYER)
        this->personnage = new Fl_PNG_Image(PLAYER_IMAGE.c_str());
    else if (type == TELEPORTATION)
        this->color = FL_GREEN;
    else if (type == WALL)
        this->wall = new Fl_PNG_Image(WALL_IMAGE.c_str());
}

Cell::~Cell()
{
    if (type == PLAYER)
        delete this->personnage;
    else if (type == WALL)
        delete this->wall;
}

void Cell::draw()
{
    if (type == PLAYER)
        personnage->draw(center.x - w / 2, center.y - h / 2, w, h);
    else if (type == WALL)
        wall->draw(center.x - w / 2, center.y - h / 2, w, h);
    else if (type == BOX_FINAL_POS)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_BLACK);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, this->color);
    }
    else
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, this->color);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, FL_BLACK);
    }
}

bool Cell::mouseClick(Point mouseLoc) // Source : Programmation Language Course
{
    if ((center.x - w / 2 < mouseLoc.x) && (mouseLoc.x < w + center.x - w / 2) && (center.y - h / 2 < mouseLoc.y) && (mouseLoc.y < h + center.y - h / 2))
        return true;
    return false;
}