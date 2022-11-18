#include "ControllerBoard.hpp"

int ControllerBoard::board_handle(int event)
{
    if (Fl::event_key() == FL_Up)
    {
        shared_board->move(shared_board->player_x, shared_board->player_y - 1);
    }
    else if (Fl::event_key() == FL_Down)
    {
        shared_board->move(shared_board->player_x, shared_board->player_y + 1);
    }
    else if (Fl::event_key() == FL_Right)
    {
        shared_board->move(shared_board->player_x + 1, shared_board->player_y);
    }
    else if (Fl::event_key() == FL_Left)
    {
        shared_board->move(shared_board->player_x - 1, shared_board->player_y);
    }

    puts("hii");
    if (shared_board->end_of_party())
    {
        std::cout << "youpi";
    }
    return 1;
}
void ControllerBoard::reset_handle()
{
    std::string aer = this->shared_board->readFileIntoString();
    this->shared_board->createBoard(aer);
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
        this->shared_board->filename = level1;
    }
    else if (choice == 1)
        this->shared_board->filename = level2;
    std::string buffer = this->shared_board->readFileIntoString();
    this->shared_board->createBoard(buffer);
}