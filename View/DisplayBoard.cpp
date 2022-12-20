#ifndef DISPLAYBOARD_CPP
#define DISPLAYBOARD_CPP

#include "DisplayBoard.hpp"

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
    this->color = color;
    this->wall = new Fl_PNG_Image(imagewall.c_str());
    if (type == PLAYER)
    {
        PlayerDisplay *player = new PlayerDisplay(center, w, h);
        this->personnage = player;
    }
}

bool Cell::contains(Point p) const
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
    std::string minpas = "min pas for this level" + std::to_string(this->boardmodel->minpas);
    fl_draw(minpas.c_str(), limitpasx + 20, limitpasy + 80);
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
std::tuple<int, int> DisplayBoard::mouseClick(Point mouseLoc)
{
    for (size_t i = 0; i < 63; i++){
        if (cells[i].mouseClick(mouseLoc))
        {
            return std::tuple<int, int>(i/8, i%8);
        }}
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
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, PLAYER, 50, 50, FL_BLACK});
            }
            else if (boardmodel->LogicCellVector[y][x]->hasBox())
            {
                if (boardmodel->LogicCellVector[y][x]->getBox()->light == false)
                    cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX, 50, 50, boardmodel->LogicCellVector[y][x]->getBox()->getColor()});
                else if (boardmodel->LogicCellVector[y][x]->getBox()->light == true)
                    cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, LIGHT_BOX, 50, 50, FL_DARK_BLUE});
            }
            else if (boardmodel->LogicCellVector[y][x]->getType() == WALL)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, WALL, 50, 50, FL_DARK_YELLOW});
            }
            else if (boardmodel->LogicCellVector[y][x]->getType() == BOX_FINAL_POS)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, BOX_FINAL_POS, 50, 50, boardmodel->LogicCellVector[y][x]->getColor()});
            }
            else if (boardmodel->LogicCellVector[y][x]->getType() == EMPTY)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, EMPTY, 50, 50, FL_BLACK});
            }
            else if (boardmodel->LogicCellVector[y][x]->getType() == TELEPORTATION)
            {
                cells.push_back(Cell{Point{boardx + 50 * ((int)x % 10) + 25, boardy + 50 * ((int)y) + 25}, TELEPORTATION, 50, 50, FL_DARK_GREEN});
            }
            else
            {
                std::cout << boardmodel->LogicCellVector[y][x]->getType() << std::endl;
            }
        }
    }
}

#endif