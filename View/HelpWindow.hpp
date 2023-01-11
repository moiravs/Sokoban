/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "DisplayBoard.hpp"
#include "CellDisplay.hpp"

class HelpWindow : public Fl_Window
{
private:
    Fl_Button *level1 = new Fl_Button(LEVEL1_X, LEVEL1_Y, LEVEL_W, LEVEL_H, "Level1");
    Fl_Button *level2 = new Fl_Button(LEVEL2_X, LEVEL2_Y, LEVEL_W, LEVEL_H, "Level2");
    Fl_Button *level3 = new Fl_Button(LEVEL3_X, LEVEL3_Y, LEVEL_W, LEVEL_H, "Level3");
    Fl_Button *level4 = new Fl_Button(LEVEL4_X, LEVEL4_Y, LEVEL_W, LEVEL_H, "Level4");

public:
    bool help = true;
    int levelsValue;
    HelpWindow();
    ~HelpWindow(){delete level1;}
    /**
     * @brief  Override the drawing function from Fl_Window, writes text
     * @retval None
     */
    void draw() override;
    /**
     * @brief  Refresh the window
     * @param  *userdata: Instance of HelpWindow
     */
    static void Time_CB(void *userdata);
    /**
     * @brief  Callback function for the widget
     * @param  *widget: the widget
     * @param  *f: Instance of HelpWindow
     * @retval None
     */
    static void windowCallback(Fl_Widget *widget, void *f);
};