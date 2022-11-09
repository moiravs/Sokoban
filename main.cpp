#include "MainWindow.cpp"


int main(int argc, char *argv[])
{
    StartWindow startwindow;
    srand(static_cast<unsigned>(time(nullptr)));

    return Fl::run();
}