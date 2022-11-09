
#include "MainWindow.hpp"
class MainWindow : public Fl_Window
{
    Board board;
    Fl_Choice *choice = new Fl_Choice(250, 25, 100, 30, "Levels");

public:
    MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Game")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
        Fl_Choice *c = choice;
        c->add("Level 1");
        c->add("Level 2");
        c->add("Level 3");
    }
    void draw() override
    {

        Fl_Window::draw();
        board.draw();
        Fl_Widget *c = choice;
        c->draw();
    }
    /*
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
    }*/

    static void Timer_CB(void *userdata)
    {
        MainWindow *o = static_cast<MainWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }
};

class StartWindow : public Fl_Window
{
private:
    Fl_Button *button = new Fl_Button(200, 200, 100, 50, "Start the game");

public:
    StartWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Start the game")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
        this->show();

        button->tooltip("Make advanced search");
        button->callback((Fl_Callback *)ad_cb);
    }
    void draw() override
    {
        Fl_Window::draw();
        Fl_Widget *b = button;
        b->draw();
    }
    static void Timer_CB(void *userdata)
    {
        StartWindow *o = static_cast<StartWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }

    static void ad_cb(Fl_Button *theButton, void *)
    {
    }
};
