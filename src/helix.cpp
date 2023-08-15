#define _USE_MATH_DEFINES
#include "helix.h"
#include <math.h>

Helix::Helix(double radius, double step) {
    if (radius <= 0) {
        throw "radius must be positive";
    }
    this->radius = radius;
    this->step = step;
};

double Helix::get_radius() const {
    return radius;
};

double Helix::get_step() const {
    return step;
};

Point Helix::get_point(double t) const {
    double x = radius * cos(t);
    double y = radius * sin(t);
    double z = t * step / (2.0 * M_PI);
    return Point(x, y, z);
};

Point Helix::get_derivative(double t) const {
    double x = -radius * sin(t);
    double y = radius * cos(t);
    double z = step / (2.0 * M_PI);
    return Point(x, y, z);
};

std::string Helix::get_name() const {
    return std::string("Helix");
}
