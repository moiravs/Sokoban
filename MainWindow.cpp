
#include "MainWindow.hpp"
class MainWindow : public Fl_Window
{
    Board board;
    Fl_Choice *choice = new Fl_Choice(500, 500, 50, 50, "Levels");

public:
    MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Game")
    {
        Fl::scheme("gtk+");
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
        Fl_Choice *c = choice;
        c->add("AHH");
        Fl_Menu_Bar *menu = new Fl_Menu_Bar(0, 0, 400, 25); // Create menubar, items..
        menu->add("&File/&Open", "^o", MyMenuCallback);
        menu->add("&File/&Save", "^s", MyMenuCallback, 0, FL_MENU_DIVIDER);
        menu->add("&File/&Quit", "^q", MyMenuCallback);
        menu->add("&Edit/&Copy", "^c", MyMenuCallback);
        menu->add("&Edit/&Paste", "^v", MyMenuCallback, 0, FL_MENU_DIVIDER);
        menu->add("&Edit/Radio 1", 0, MyMenuCallback, 0, FL_MENU_RADIO);
        menu->add("&Edit/Radio 2", 0, MyMenuCallback, 0, FL_MENU_RADIO | FL_MENU_DIVIDER);
        menu->add("&Edit/Toggle 1", 0, MyMenuCallback, 0, FL_MENU_TOGGLE);                 // Default: off
        menu->add("&Edit/Toggle 2", 0, MyMenuCallback, 0, FL_MENU_TOGGLE);                 // Default: off
        menu->add("&Edit/Toggle 3", 0, MyMenuCallback, 0, FL_MENU_TOGGLE | FL_MENU_VALUE); // Default: on

        // Example: show how we can dynamically change the state of item Toggle #2 (turn it 'on')
        {
            Fl_Menu_Item *item = (Fl_Menu_Item *)menu->find_item("&Edit/Toggle 2"); // Find item
            if (item)
                item->set(); // Turn it on
            else
                fprintf(stderr, "'Toggle 2' item not found?!\n"); // (optional) Not found? complain!
        }
    }
    static void MyMenuCallback(Fl_Widget *w, void *)
    {
        Fl_Menu_Bar *bar = (Fl_Menu_Bar *)w;      // Get the menubar widget
        const Fl_Menu_Item *item = bar->mvalue(); // Get the menu item that was picked

        char ipath[256];
        bar->item_pathname(ipath, sizeof(ipath)); // Get full pathname of picked item

        fprintf(stderr, "callback: You picked '%s'", item->label()); // Print item picked
        fprintf(stderr, ", item_pathname() is '%s'", ipath);         // ..and full pathname

        if (item->flags & (FL_MENU_RADIO | FL_MENU_TOGGLE))
        {                                                                   // Toggle or radio item?
            fprintf(stderr, ", value is %s", item->value() ? "on" : "off"); // Print item's value
        }
        fprintf(stderr, "\n");
        if (strcmp(item->label(), "&Quit") == 0)
        {
            exit(0);
        }
    }
    void draw() override
    {

        Fl_Window::draw();
        board.draw();
        Fl_Widget *c = choice;
        c->draw();
    }
    int handle(int event) override
    {
        switch (event)
        {
        case FL_MOVE:
            board.mouseMove(Point{Fl::event_x(), Fl::event_y()});
            return 1;
        case FL_PUSH:
            board.mouseClick(Point{Fl::event_x(), Fl::event_y()});
            return 1;
        case FL_KEYDOWN:
            board.keyPressed(Fl::event_key());
            return 1;
        }
        return 0;
    }

    static void Timer_CB(void *userdata)
    {
        MainWindow *o = static_cast<MainWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }
};

class StartWindow : public Fl_Window
{
private:
    Fl_Button *button = new Fl_Button(200, 200, 100, 50, "Start the game");

public:
    StartWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Start the game")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
        this->show();

        button->tooltip("Make advanced search");
        button->callback((Fl_Callback *)ad_cb);
    }
    void draw() override
    {
        Fl_Window::draw();
        Fl_Widget *b = button;
        b->draw();
    }
    static void Timer_CB(void *userdata)
    {
        StartWindow *o = static_cast<StartWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }

    static void ad_cb(Fl_Button *theButton, void *)
    {
    }
};
