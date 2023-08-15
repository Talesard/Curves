#include "ellipse.h"
#include <math.h>

Ellipse::Ellipse(double radius_x, double radius_y) {
    if (radius_x <= 0 || radius_y <= 0) {
        throw "radius must be positive";
    }
    this->radius_x = radius_x;
    this->radius_y = radius_y;
}

std::pair<double, double> Ellipse::get_radii() const {
    return std::pair<double, double>(radius_x, radius_y);
}

Point Ellipse::get_point(double t) const {
    double x = radius_x * cos(t);
    double y = radius_y * sin(t);
    double z = 0;
    return Point(x, y, z);
}

Point Ellipse::get_derivative(double t) const {
    double dx = -radius_x * sin(t);
    double dy = radius_y * cos(t);
    double dz = 0;
    return Point(dx, dy, dz);
}

std::string Ellipse::get_name() const {
    return std::string("Ellipse");
}
