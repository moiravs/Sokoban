#include "Constants.hpp"
#include "Board.hpp"
class ControllerBoard
{
private:
    std::shared_ptr<Board> boardmodel;
    Fl_Widget Board;

public:
    ControllerBoard(std::shared_ptr<Board> board)
    {
        boardmodel = board;
    };
    //event inside -> inside a widget or not
    
};
ControllerBoard::handle(){
    if (Fl_Event_Key == FL_Up){

    }
}