#include "DisplayBoard.hpp"
#include "CellDisplay.hpp"

class HelpWindow : public Fl_Window
{
private:
public:
    HelpWindow();
    void draw() override;
    static void Time_CB(void *userdata);
    void window_non_static_cb(Fl_Widget *widget);
    static void windowCallback(Fl_Widget *widget, void *f);
};