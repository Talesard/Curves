#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <random>
#include <algorithm> 
#include <numeric>
#include <chrono>
#include <memory>

#include "curveslib.h"

#define CURVES_COUNT 20

#define OMP_VERSION


std::vector<std::shared_ptr<Curve3D>> create_curves(int n) {
    if (n < 1) throw "curves count must be > 1";
    std::vector<std::shared_ptr<Curve3D>> curves(n);

    std::random_device rd;
    std::mt19937 rng(rd());
    rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> uni(0, 2);
    std::uniform_real_distribution<double> und(1.0, 10.0);

    for (auto i = 0; i < n; i++) {
        auto curve_type = uni(rng);
        switch (curve_type) {
        case 0:
            curves[i] = std::shared_ptr<Curve3D>(new Circle(und(rng)));
            break;
        case 1:
            curves[i] = std::shared_ptr<Curve3D>(new Ellipse(und(rng), und(rng)));
            break;
        case 2:
            curves[i] = std::shared_ptr<Curve3D>(new Helix(und(rng), und(rng)));
            break;
        }
    }

    // what if there won't be any circles for the next step? -> +2 circles
    curves.push_back(std::shared_ptr<Curve3D>(new Circle(und(rng))));
    curves.push_back(std::shared_ptr<Curve3D>(new Circle(und(rng))));

    return curves;
}

void print_points_derivatives(const std::vector<std::shared_ptr<Curve3D>>& curves, double t) {
    std::cout << "\nAll curves:" << std::endl;
    for (auto curve : curves) {
        std::cout << curve->get_name() << ": point: " << curve->get_point(t) 
        << " deriv: " << curve->get_derivative(t) << std::endl;
    }
}

std::vector<std::shared_ptr<Circle>> filter_circles(const std::vector<std::shared_ptr<Curve3D>>& curves) {
    std::vector<std::shared_ptr<Circle>> circles;
    for (auto curve : curves) {
        auto tmp = dynamic_cast<Circle*>(curve.get());
        if (tmp != nullptr) {
            circles.push_back(std::shared_ptr<Circle>(tmp));
        }
    }
    return circles;
}

int main(int argc, char const *argv[]) {
    // Populate a container (e.g. vector or list) of objects
    // of these types created in random manner with random parameters
    std::vector<std::shared_ptr<Curve3D>> curves = create_curves(CURVES_COUNT);

    // Print coordinates of points and derivatives of all curves in the container at t=PI/4
    print_points_derivatives(curves, M_PI / 4.0);

    // Populate a second container that would contain only circles from the first container
    std::vector<std::shared_ptr<Circle>> circles = filter_circles(curves);

    // Sort the second container in the ascending order of circles’ radii
    std::sort(circles.begin(), circles.end(), [](const auto& v1, const auto& v2) {
        return v1->get_radius() < v2->get_radius();
    });
    std::cout << "\nThe circles are sorted by radius:" << std::endl;
    for (auto circle : circles) std::cout << circle->get_radius() << " ";
    std::cout << std::endl;
    

    // Compute the total sum of radii of all curves in the second container
    auto start = std::chrono::steady_clock::now();
    auto radius_sum = std::accumulate(circles.begin(), circles.end(), 0.0,
        [](double acc, auto& v){return acc + v->get_radius();});
    auto end = std::chrono::steady_clock::now();
    std::cout << "\nRadii sum: " << radius_sum << std::endl;
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << delta.count() << "ms" << std::endl;

    // OpenMP version
    #ifdef OMP_VERSION
    auto radius_sum_omp = 0.0;
    start = std::chrono::steady_clock::now();
    #pragma omp parallel for reduction(+:radius_sum_omp)
    for (auto i = 0; i < circles.size(); i++) {
        radius_sum_omp += circles[i]->get_radius();
    }
    end = std::chrono::steady_clock::now();
    std::cout << "\nRadii sum OMP: " << radius_sum_omp << std::endl;
    delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << delta.count() << "ms" << std::endl;
    #endif
    return 0;
}
