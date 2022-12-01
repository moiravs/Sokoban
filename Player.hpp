class Player
{
    int x;
    int y;
    unsigned int stepsCount = 0;
public:
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    void incrementSteps();
};