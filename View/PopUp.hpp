#include "DisplayBoard.hpp"
#include "CellDisplay.hpp"

class PopUp : public Fl_Window
{
private:
public:
    Fl_Choice *levels = new Fl_Choice(100, 150, 200, 50);

    PopUp();
    void draw() override;
    static void Time_CB(void *userdata);
    void window_non_static_cb(Fl_Widget *widget);
    static void windowCallback(Fl_Widget *widget, void *f);
};