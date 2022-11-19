
#include "ControllerBoard.hpp"

int ControllerBoard::board_handle(int event)
{
    this->boardModel->pas += 1;
    if (Fl::event_key() == FL_Up)
    {
        boardModel->move(boardModel->player_x, boardModel->player_y - 1);
    }
    else if (Fl::event_key() == FL_Down)
    {
        boardModel->move(boardModel->player_x, boardModel->player_y + 1);
    }
    else if (Fl::event_key() == FL_Right)
    {
        boardModel->move(boardModel->player_x + 1, boardModel->player_y);
    }
    else if (Fl::event_key() == FL_Left)
    {
        boardModel->move(boardModel->player_x - 1, boardModel->player_y);
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