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
public:
    HelpWindow();
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