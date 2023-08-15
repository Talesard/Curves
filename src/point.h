#include <iostream>

class Point {
public:
    double x, y, z;

    Point(double x, double y, double z): x(x), y(y), z(z){};
    
    friend std::ostream& operator<< (std::ostream &out, const Point &point) {
        out << "(" << point.x << "; " << point.y << "; " << point.z << ")";
        return out;
    }
};
