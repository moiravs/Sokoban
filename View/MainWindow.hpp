#include "DisplayBoard.hpp"

class MainWindow : public Fl_Window
{

    std::shared_ptr<BoardModel> boardModel;
    ControllerBoard *control;
    DisplayBoard *display;
    Fl_Button *reset;
    Fl_Button *custom;
    Fl_Choice *levels;
    const char *pas;
    Fl_Text_Buffer *buff;

public:
    MainWindow(std::shared_ptr<BoardModel> boardModel);

    static void MyMenuCallback(Fl_Widget *w, void *);
    void draw() override;

    int handle(int event) override;

    static void Timer_CB(void *userdata);
};

class StartWindow : public Fl_Window
{
private:
    Fl_Button *button = new Fl_Button(300, 300, 400, 50, "Andrius Ezerskis & Moïra Vanderslagmolen");

public:
    int wait = 0;

    StartWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "SOKOBAN")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Time_CB, this);
        resizable(this);
        this->show();
    }
    void draw() override
    {
        Fl_Window::draw();
        fl_draw("SOKOBAN", 300, 300);
    }
    static void Time_CB(void *userdata)
    {
        StartWindow *o = static_cast<StartWindow *>(userdata);
        o->wait++;
        if (o->wait == 10)
        {
            sleep(1);
            o->hide();
        }
        Fl::repeat_timeout(1.0 / refreshPerSecond, Time_CB, userdata);
    }
};