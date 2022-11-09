#include "Board.hpp"


void BoardController::mouseMove(Point mouseLoc)
{
    for (auto &v : boardModel.getCells())
        for (auto &c: v)
            c.mouseMove(mouseLoc);
}
void BoardController::mouseClick(Point mouseLoc)
{
    for (auto &v : cells)
        for (auto &c : v)
            c.mouseClick(mouseLoc);
}

void BoardController::keyPressed(int keyCode){
    return;
}

void BoardController::getBoard(std::string fileName){
    std::ifstream fileStream(fileName);
}

void BoardModel::initialize(){
    cells.clear();
    for (unsigned short x = 0; x < 10; x++){
        cells.push_back({});
        for (int y = 0; y < 10; y++){
            cells[x].push_back({{50*x+100, 50*y+100}, 50, 50, 1});
        }
    }
}

std::vector<std::vector<CellModel>> BoardModel::getCells(){
    return cells;
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