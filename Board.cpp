#include "Board.hpp"


void BoardController::mouseMove(Point mouseLoc)
{
    for (auto &v : cells)
        for (auto &c: v)
            c.mouseMove(mouseLoc);
}
void BoardController::mouseClick(Point mouseLoc)
{
    for (auto &v : cells)
        for (auto &c : v)
            c.mouseClick(mouseLoc);
}

void Board::keyPressed(int keyCode){
    return;
}

void BoardController::getBoard(string fileName){
    std::ifstream fileStream(fileName);
}

void BoardModel::initialize(){
    cells.clear();
    for (unsigned short x = 0; x < 10; x++){
        cells.push_back({});
        for (int y = 0; y < 10; y++){
            cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, 1});
        }
    }
}

void BoardView::clear(){
    return;
}


void BoardView::draw()
{
    for (auto &v : cells)
        for (auto &c: v)
            c.draw();
}