#include <optional>
#include <iostream>
#include "cmath"
#include "point.cpp"

class Panel {       // The class

public:
    //Constructor
    //triangle
    Panel(int n, Point a, Point b, Point c):
            corners(n),
            p1(a),
            p2(b),
            p3(c)
    {
    }
    //quad
    Panel(int n, Point a, Point b, Point c, Point d):
            corners(n),
            p1(a),
            p2(b),
            p3(c),
            p4(d)
    {
    }

public:
    int corners;
    Point p1;
    Point p2;
    Point p3;
    Point p4;

    float maxLengthEdge()
    {
        float lmax;

        //length of edges
        //4 corners
        if(corners==4){
            float l12 = length(p1, p2);
            float l23 = length(p2, p3);
            float l34 = length(p3, p4);
            float l41 = length(p1, p4);
            lmax = fmax( fmax(l12, l23), fmax(l34, l41));
        }
        else {
            float l12 = length(p1, p2);
            float l23 = length(p2, p3);
            float l31 = length(p1, p3);
            lmax = fmax( fmax(l12, l23), l31);

        }
        return lmax;
    }

    //float aspectRatio(Point p1, Point p2, Point p3, std::optional<Point> p4)
    float aspectRatio()
    {
        float lmax;
        float lmin;
        //length of edges
        //4 corners
        if(corners==4){
            float l12 = length(p1, p2);
            float l23 = length(p2, p3);
            float l34 = length(p3, p4);
            float l41 = length(p1, p4);

            lmax = fmax( fmax(l12, l23), fmax(l34, l41));
            lmin = fmin( fmin(l12, l23), fmin(l34, l41));
        }
        else {
            float l12 = length(p1, p2);
            float l23 = length(p2, p3);
            float l31 = length(p1, p3);

            lmax = fmax( fmax(l12, l23), l31);
            lmin = fmin( fmin(l12, l23), l31);
        }
        return lmax/lmin;
    }

private:
    float length(Point p1, Point p2)
    {
        return pow( pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2)+pow(p2.z-p1.z,2), 0.5);
    }

};



