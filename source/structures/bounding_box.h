#pragma once

#include <string>
#include "structures/vector2d.h"

class BoundingBox {
public:
    // Public fields to store bounding box coordinates
    double x_min;
    double x_max;
    double y_min;
    double y_max;

    // Constructors
    BoundingBox(); // Default constructor
    BoundingBox(double x_min, double x_max, double y_min, double y_max); // Parameterized constructor

    // Check if a given position is contained within the bounding box
    bool contains(const Vector2d<double>& position) const;

    // Retrieve a specific quadrant of the bounding box
    BoundingBox get_quadrant(std::uint8_t quadrant_index) const;

    // Utility methods
    std::string get_string() const; // Returns a string representation of the bounding box
    double get_diagonal() const;    // Calculates the diagonal length of the bounding box
    void plotting_sanity_check();   // Ensures the bounding box dimensions are valid
    BoundingBox get_scaled(std::uint32_t scaling_factor) const; // Returns a scaled version of the bounding box
};
