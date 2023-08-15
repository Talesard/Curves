#include "curve.h"

class Helix : public Curve3D {
private:
    double radius;
    double step;
public:
    Helix(double radius, double step);
    double get_radius() const;
    double get_step() const;
    Point get_point(double t) const override;
    Point get_derivative(double t) const override;
    virtual std::string get_name() const override;
};
