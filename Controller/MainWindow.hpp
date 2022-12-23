/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "../View/DisplayBoard.hpp"
#include "../View/CellDisplay.hpp"

class PopUp : public Fl_Window
{
private:
public:
    Fl_Choice *levels = new Fl_Choice(200, 200, 200, 50, "ChooseLevel");

    PopUp() : Fl_Window(400, 400, 400, 400, "SOKOBAN")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Time_CB, this);
        resizable(this);
        this->show();

        levels->add("Level 1");
        levels->add("Level 2");
        levels->add("Level 3");
        levels->show();
        levels->callback(windowCallback, this);
    }
    void draw() override
    {
        Fl_Window::draw();
        fl_draw("SOKOBAN", 300, 300);
    }
    static void Time_CB(void *userdata)
    {
        Fl::repeat_timeout(1.0 / refreshPerSecond, Time_CB, userdata);
    }
    void window_non_static_cb(Fl_Widget *widget)
    {
        this->hide();
    }

    static void windowCallback(Fl_Widget *widget, void *f)
    {
        ((PopUp *)f)->window_non_static_cb(widget);
    }
};
class MainWindow : public Fl_Window
{
    std::shared_ptr<BoardModel> boardModel;
    DisplayBoard *display;
    const char *steps;
    Fl_Text_Buffer *buff;
    PopUp *popUp;

public:
    MainWindow(std::shared_ptr<BoardModel> boardModel, PopUp *popUp);
    static void MyMenuCallback(Fl_Widget *w, void *);
    void draw() override;
    int handle(int event) override;
    static void windowCallback(Fl_Widget *widget, void *);
    static void Timer_CB(void *userdata);
    static void resetLevelCallback(Fl_Widget *widget, void *board_model);
    static void reset_min_pas_cb(Fl_Widget *widget, void *);
    static void changeLevelCallback(Fl_Widget *widget, void *board_Model);
    void saveMinimumSteps();
    static void resetMinStepsCallback(Fl_Widget *w, void *f);
};

class StartWindow : public Fl_Window
{
private:
    Fl_Button *button = new Fl_Button(300, 300, 400, 50, "Andrius Ezerskis & Moïra Vanderslagmolen");
    int wait = 0;

public:
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