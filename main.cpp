#include "MainWindow.cpp"


int main(int argc, char *argv[])
{
    StartWindow startwindow;
    startwindow.show(argc, argv);
    srand(static_cast<unsigned>(time(nullptr)));
    MainWindow window;
    window.show(argc, argv);
    return Fl::run();
}