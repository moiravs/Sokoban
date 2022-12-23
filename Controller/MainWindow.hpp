/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "../View/DisplayBoard.hpp"
#include "../View/CellDisplay.hpp"
#include "../View/PopUp.hpp"
#include "../View/HelpWindow.hpp"
#include "../View/StartWindow.hpp"

class MainWindow : public Fl_Window
{
    std::shared_ptr<BoardModel> boardModel;
    DisplayBoard *display;
    const char *steps;
    Fl_Text_Buffer *buff;
    PopUp *popUp;
    HelpWindow *helpWindow;

public:
    MainWindow(std::shared_ptr<BoardModel> boardModel, PopUp *popUp, HelpWindow *helpWindow);
    static void MyMenuCallback(Fl_Widget *w, void *);
    void draw() override;
    int handle(int event) override;
    static void windowCallback(Fl_Widget *widget, void *);
    static void Timer_CB(void *userdata);
    static void resetLevelCallback(Fl_Widget *widget, void *board_model);
    static void changeLevelCallback(Fl_Widget *widget, void *board_Model);
    static void resetMinStepsCallback(Fl_Widget *w, void *f);
    static void helpCallback(Fl_Widget *w, void *f);
};

