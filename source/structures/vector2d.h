#pragma once
#include <stdexcept>
#include <array>

template <typename T>
class Vector2d {
public:
    // Default constructor initializes components to zero
    Vector2d() : components_{ T(0), T(0) } {}

    // Constructor to initialize both components directly
    Vector2d(T x, T y) : components_{ x, y } {}

    // Access operator [] for reading components
    T operator[](std::size_t index) const {
        if (index >= components_.size()) {
            throw std::out_of_range("Index out of range for Vector2d");
        }
        return components_[index];
    }

    // Access operator [] for modifying components
    T& operator[](std::size_t index) {
        if (index >= components_.size()) {
            throw std::out_of_range("Index out of range for Vector2d");
        }
        return components_[index];
    }

    // Set method to update both components
    void set(T x, T y) {
        components_[0] = x;
        components_[1] = y;
    }

    // Addition of two vectors
    Vector2d operator+(const Vector2d& other) const {
        return Vector2d(components_[0] + other.components_[0], components_[1] + other.components_[1]);
    }

    // Subtraction of two vectors
    Vector2d operator-(const Vector2d& other) const {
        return Vector2d(components_[0] - other.components_[0], components_[1] - other.components_[1]);
    }

    // Multiplication by a scalar
    Vector2d operator*(const T& scalar) const {
        return Vector2d(components_[0] * scalar, components_[1] * scalar);
    }

    // Division by a scalar
    Vector2d operator/(const T& scalar) const {
        if (scalar == T(0)) {
            throw std::invalid_argument("Division by zero");
        }
        return Vector2d(components_[0] / scalar, components_[1] / scalar);
    }

    // Equality operator
    bool operator==(const Vector2d& other) const {
        return components_[0] == other.components_[0] && components_[1] == other.components_[1];
    }

private:
    std::array<T, 2> components_;
};

