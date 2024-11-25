#pragma once
// Function to calculate the acceleration of a body
template <typename T>
static Vector2d<T> calculate_acceleration(const Vector2d<T>& force, T mass) {
    if (mass == 0) {
        throw std::invalid_argument("Mass cannot be zero.");
    }
    // Newton's second law: a = F / m
    return force / mass;
}

// Function to calculate the velocity of a body
template <typename T>
static Vector2d<T> calculate_velocity(const Vector2d<T>& initial_velocity, const Vector2d<T>& acceleration, T time) {
    // v = v0 + a * t
    return initial_velocity + (acceleration * time);
}