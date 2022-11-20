
#include "ControllerBoard.hpp"
#include "Board.hpp"

int ControllerBoard::board_handle(int event)
{

    if (Fl::event_key() == FL_Up)
    {
        if (boardModel->move(boardModel->player_y - 1, boardModel->player_x))
            this->boardModel->pas += 1;
    }
    else if (Fl::event_key() == FL_Down)
    {
        if (boardModel->move(boardModel->player_y + 1, boardModel->player_x))
            this->boardModel->pas += 1;
    }
    else if (Fl::event_key() == FL_Right)
    {
        if (boardModel->move(boardModel->player_y, boardModel->player_x + 1))
            this->boardModel->pas += 1;
    }
    else if (Fl::event_key() == FL_Left)
    {
        if (boardModel->move(boardModel->player_y, boardModel->player_x - 1))
            this->boardModel->pas += 1;
    }

    puts("hii");
    if (boardModel->end_of_party())
    {
        std::cout << "youpi";
    }
    puts("ahh9");
    return 1;
}
void ControllerBoard::reset_handle()
{
    std::string aer = this->boardModel->readFileIntoString();
    this->boardModel->createBoard(aer);
    puts("aeeaa");
}
void ControllerBoard::level_change(int choice)
{
    std::cout << choice << std::endl;
    if (choice == -1)
    {
        return;
    }
    if (choice == 0)
    {
        this->boardModel->filename = level1;
    }
    else if (choice == 1)
        this->boardModel->filename = level2;
    std::string buffer = this->boardModel->readFileIntoString();
    this->boardModel->createBoard(buffer);
}