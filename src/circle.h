#include "curve.h"

class Circle : public Curve3D {
private:
    double radius;
public:
    Circle(double radius);
    double get_radius() const;
    virtual Point get_point(double t) const override;
    virtual Point get_derivative(double t) const override;
    virtual std::string get_name() const override;
};
