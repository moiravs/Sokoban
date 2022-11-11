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

std::string BoardController::readFileIntoString(std::string fileName){
    std::ifstream ifs(fileName);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));
}

std::vector<std::vector<int>> BoardController::getBoard(std::string fileContent){
    std::vector<std::vector<int>> lines;
    std::vector<int> line;
    for (size_t index=0; index < fileContent.size(); index++){
        if (fileContent[index] == '\n'){
            lines.push_back(line);
            std::vector<int> line;
        }
        else if (fileContent[index] != ' '){
            line.push_back(static_cast<int>(fileContent[index]));
        }
    }
    return lines;
}

/*void BoardModel::initialize(){
    cells.clear();
    for (unsigned short x = 0; x < 10; x++){
        cells.push_back({});
        for (int y = 0; y < 10; y++){
            cells[x].push_back({{50*x+100, 50*y+100}, 50, 50, 1});
        }
    }
}*/

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