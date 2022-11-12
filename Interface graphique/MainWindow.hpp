#include "Board.hpp"

class MainWindowModel : public Fl_Window
{
};


class MainWindowController : public Fl_Window
{
private:
    BoardController board;
    MainWindowView MWView;
    MainWindowModel MWModel;

public:
    int handle(int event) override
    {
        switch (event)
        {
        case FL_MOVE:
            board.mouseMove(Point{Fl::event_x(), Fl::event_y()});
            return 1;
        case FL_PUSH:
            board.mouseClick(Point{Fl::event_x(), Fl::event_y()});
            return 1;
        case FL_KEYDOWN:
            board.keyPressed(Fl::event_key());
            return 1;
        }
        return 0;
    }
};
