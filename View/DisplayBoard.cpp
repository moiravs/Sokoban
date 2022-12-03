#ifndef DISPLAYBOARD_CPP
#define DISPLAYBOARD_CPP

#include "DisplayBoard.hpp"
/*
Box::Box(){
    this->wall = new Fl_JPEG_Image(imagewall);
}

void Box::draw(){
    Fl_JPEG_Image *wall = new Fl_JPEG_Image(imagewall);
    Fl_Image *hihi = wall;
    hihi->draw(center.x - w / 2, center.y - h / 2, w, h);
    fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, FL_BLUE);
}

Player::Player(){
    this->personnage = new Fl_JPEG_Image(imageplayer);
}

void Player::draw(){
    Fl_Image *hihi = this->personnage;
    hihi->draw(center.x - w / 2, center.y - h / 2, w, h);
    fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, FL_BLUE);
}
*/

Cell::Cell(Point center, int type, int w, int h) : center{center}, type{type}, w{w}, h{h}
{
    this->personnage = new Fl_JPEG_Image(imageplayer.c_str());
    this->wall = new Fl_PNG_Image(imagewall.c_str());
}

void Cell::draw()
{
    
    if (type == PLAYER)
    {
        //Fl_Image *hihi = this->personnage;
        //hihi->draw(center.x - w / 2, center.y - h / 2, w, h);
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_BLUE);

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
        Fl_Image *picture = this->wall;
        picture->draw(center.x - w / 2, center.y - h / 2, w, h);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
    else if (type == BOX_FINAL_POS)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_YELLOW);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
    else if (type == LIGHT_BOX)
    {
        fl_draw_box(FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, FL_DARK_BLUE);
        fl_draw_box(FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
    }
}

bool Cell::mouseClick(Point mouseLoc)
{
    if ((center.x - w / 2 < mouseLoc.x) && (mouseLoc.x < w + center.x - w / 2) && (center.y - h / 2 < mouseLoc.y) && (mouseLoc.y < h + center.y - h / 2))
    {
        puts("got it");
        return true;
    }
    return false;
}

void DisplayBoard::draw()
{
    for (auto &c : cells)
        c.draw();

    std::string pas = "pas " + std::to_string(this->boardmodel->pas);
    fl_draw(pas.c_str(), pasx, pasy);
    std::string limitpas = "limite de pas " + std::to_string(this->boardmodel->limitpas);
    fl_draw(limitpas.c_str(), limitpasx, limitpasy);
}

DisplayBoard::DisplayBoard(std::shared_ptr<BoardModel> board) : Fl_Box(boardx, boardy, boardw, boardh)
{
    this->boardmodel = board;
    this->update();
}

void DisplayBoard::printBoard()
{
    for (size_t i = 0; i < boardmodel->getBoard().size(); i++)
    {
        for (size_t j = 0; j < boardmodel->getBoard()[0].size(); j++)
        {
            std::cout << boardmodel->getBoard()[i][j] << " ";
        }
        std::cout << "\n";
    }
}
void DisplayBoard::mouseClick(Point mouseLoc)
{
    for (auto &c : cells)
        c.mouseClick(mouseLoc);
}

void DisplayBoard::update()
{
    cells.clear();
    for (size_t y = 0; y < boardmodel->getBoard().size(); y++)
    {
        for (size_t x = 0; x < boardmodel->getBoard()[y].size(); x++)
        {
            if (boardmodel->LogicCellVector[y][x]->hasPlayer())
            {

                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, PLAYER, 50, 50});
            }
            else if (boardmodel->LogicCellVector[y][x]->hasBox())
            {
                if (boardmodel->LogicCellVector[y][x]->getBox()->light == false)
                    cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX, 50, 50});
                else if (boardmodel->LogicCellVector[y][x]->getBox()->light == true)
                    cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, LIGHT_BOX, 50, 50});
            }
            else if (boardmodel->LogicCellVector[y][x]->getType() == WALL)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, WALL, 50, 50});
            }
            else if (boardmodel->LogicCellVector[y][x]->getType() == BOX_FINAL_POS)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX_FINAL_POS, 50, 50});
            }
            else if (boardmodel->LogicCellVector[y][x]->getType() == EMPTY)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, EMPTY, 50, 50});
            }
            else {
                //std::cout << boardmodel->LogicCellVector[y][x]->getType() << std::endl;
            }
        }
    }
}

#endif