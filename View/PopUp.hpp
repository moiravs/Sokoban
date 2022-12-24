/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "DisplayBoard.hpp"
#include "CellDisplay.hpp"

class PopUp : public Fl_Window
{
private:
public:
    Fl_Choice *levels = new Fl_Choice(100, 150, 200, 50);

    PopUp();
    /**
     * @brief  Override the drawing function from Fl_Window, draw the levels
     * @retval None
     */
    void draw() override;
    /**
     * @brief  Refresh the window
     * @param  *userdata: Instance of PopUp
     */
    static void Time_CB(void *userdata);
    /**
     * @brief  Callback function for the widget
     * @param  *widget: the widget
     * @param  *f: Instance of PopUp
     * @retval None
     */
    static void windowCallback(Fl_Widget *widget, void *f);
};