#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>


struct Coordinate {
    double x;
    double y;
    double z;
};

double calculateNorm(Coordinate& c) {
    double x_squared = c.x * c.x;
    double y_squared = c.y * c.y;
    double z_squared = c.z * c.z;
    return std::sqrt(x_squared + y_squared + z_squared);
}

int main() {
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distribution(-100.0, 100.0);
    Coordinate c;
    c.x = distribution(gen);
    c.y = distribution(gen);
    c.z = distribution(gen);
    double norm = calculateNorm(c);
    std::cout << "norm({"
              << c.x << ", " <<  c.y << ", " <<  c.z
              << "}): " << norm << '\n';
    return 0;
}
