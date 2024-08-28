#ifndef MY_VECTOR2D_HPP
#define MY_VECTOR2D_HPP

#include <iostream>

class Vector2D {
public:
    double x;
    double y;

    Vector2D() : x(0), y(0) {}
    Vector2D(double x, double y) : x(x), y(y) {}

    // Indexing operator for accessing x and y
    double& operator[](size_t index) {
        if (index == 0) {
            return x;
        } else if (index == 1) {
            return y;
        } else {
            throw std::out_of_range("Vector2D index out of range");
        }
    }

    // Const version of indexing operator for const objects
    const double& operator[](size_t index) const {
        if (index == 0) {
            return x;
        } else if (index == 1) {
            return y;
        } else {
            throw std::out_of_range("Vector2D index out of range");
        }
    }

    // Method to print the vector
    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

#endif  
