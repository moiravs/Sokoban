class Box
{

    int x;
    int y;
    bool bloquée;

public:
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }
    int getX()
    {
        return (this->x);
    }
    int getY()
    {
        return (this->y);
    }
};