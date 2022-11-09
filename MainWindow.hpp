#include "Board.hpp"

class MainWindowModel : public Fl_Window
{
};

class MainWindowView : Fl_Window
{
private:
    Fl_Choice *choice = new Fl_Choice(250, 25, 100, 30, "Levels");
    Board board;

public:
    MainWindowView() : Fl_Window(500, 500, windowWidth, windowHeight, "Game")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
        Fl_Choice *c = choice;
        c->add("Level 1");
        c->add("Level 2");
        c->add("Level 3");
    };
    void draw() override
    {

        Fl_Window::draw();
        board.draw();
        Fl_Widget *c = choice;
        c->draw();
    }
    static void Timer_CB(void *userdata);
};

class MainWindowController : Fl_Window
{
private:
    Board board;
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
