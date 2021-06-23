
class Point {       // The class
public:
    int idx;
    float x;
    float y;
    float z;

public:
    //constructor
    Point(int idx, float x, float y, float z)
    {
        this->idx=idx,
        this->x=x,
        this->y=y,
        this->z=z;
    };

    //standard constructor
    Point():
            idx(0),
            x(0),
            y(0),
            z(0)
    {
    };


};