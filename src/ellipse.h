#include "curve.h"

class Ellipse : public Curve3D {
private:
    double radius_x;
    double radius_y;
public:
    Ellipse(double radius_x, double radius_y);
    std::pair<double, double> get_radii() const;
    virtual Point get_point(double t) const override;
    virtual Point get_derivative(double t) const override;
    virtual std::string get_name() const override;
};
