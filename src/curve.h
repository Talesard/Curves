#pragma once
#include "point.h"

class Curve3D {
public:
    virtual Point get_point(double t) const = 0;
    virtual Point get_derivative(double t) const = 0;

    // It's just for beauty. Another interesting way is used to search for circles
    virtual std::string get_name() const = 0;
    
    virtual ~Curve3D() {}
};
