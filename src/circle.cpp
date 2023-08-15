#include "circle.h"
#include <math.h>

Circle::Circle(double radius) {
    if (radius <= 0) {
        // gcc, where is the invalid argument exception???
        throw "radius must be positive";
    }
    this->radius = radius;
}

double Circle::get_radius() const {
    return radius;
};

Point Circle::get_point(double t) const {
    double x = radius * cos(t);
    double y = radius * sin(t);
    double z = 0;
    return Point(x, y, z);
}

Point Circle::get_derivative(double t) const {
    double dx = -radius * sin(t);
    double dy = radius * cos(t);
    double dz = 0;
    return Point(dx, dy, dz);
}

std::string Circle::get_name() const {
    return std::string("Circle");
}
