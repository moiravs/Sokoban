/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "DisplayBoard.hpp"
#include "CellDisplay.hpp"
class MainWindow : public Fl_Window
{
    std::shared_ptr<BoardModel> boardModel;
    ControllerBoard *control;
    DisplayBoard *display;
    const char *pas;
    Fl_Text_Buffer *buff;

public:
    MainWindow(std::shared_ptr<BoardModel > boardModel);
    static void MyMenuCallback(Fl_Widget *w, void *);
    void draw() override;
    int handle(int event) override;
    static void window_cb(Fl_Widget *widget, void *);
    static void Timer_CB(void *userdata);
    static void reset_level_cb(Fl_Widget *widget, void * board_model);
    static void reset_min_pas_cb(Fl_Widget *widget, void *);
    static void level_change(Fl_Widget *widget, void *board_Model);
    void level_change_non_static(Fl_Widget *widget);
    void reset_level_non_static(Fl_Widget *widget);
    void saveminpas() ;
    void resetminpas_cb();
    static void resetminpas_cb_static(Fl_Widget *w, void *f);
    void window_non_static_cb(Fl_Widget *widget);
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