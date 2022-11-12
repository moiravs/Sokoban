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