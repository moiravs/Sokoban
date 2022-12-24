#include "../View/DisplayBoard.hpp"
#include "../View/CellDisplay.hpp"

class StartWindow : public Fl_Window
{
private:
    Fl_Button *button = new Fl_Button(300, 300, 400, 50, "Andrius Ezerskis & Moïra Vanderslagmolen");
    int wait = 0;

public:
    StartWindow();
    void draw() override;
    static void Time_CB(void *userdata);
};