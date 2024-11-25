#include "simulation/naive_sequential_simulation.h"
#include "simulation/constants.h"
#include "physics/gravitation.h"
#include "physics/mechanics.h"

#include <cmath>

void NaiveSequentialSimulation::calculate_forces(Universe& universe)
{
    // Initialize forces to zero for all bodies
    for (std::uint32_t i = 0; i < universe.num_bodies; ++i) {
        universe.forces[i] = Vector2d<double>(0.0, 0.0);  // Reset forces
    }

    // Compute forces acting on each body
    for (std::uint32_t i = 0; i < universe.num_bodies; ++i) {
        for (std::uint32_t j = i + 1; j < universe.num_bodies; ++j) {
            // Calculate the distance between body i and body j
            Vector2d<double> displacement = universe.positions[j] - universe.positions[i];
            double distance = std::sqrt(displacement[0] * displacement[0] + displacement[1] * displacement[1]);

            // Check to avoid zero distance, which would lead to division by zero
            if (distance == 0) {
                throw std::invalid_argument("Bodies are at the same position.");
            }

            // Calculate the gravitational force between body i and body j
            double force_magnitude = gravitational_force(universe.weights[i], universe.weights[j], distance);

            // Normalize the displacement vector to get the direction
            Vector2d<double> force_direction = displacement / distance;

            // Calculate the force vector between body i and body j
            Vector2d<double> force = force_direction * force_magnitude;

            // Apply forces to both bodies (action-reaction)
            universe.forces[i] = universe.forces[i] + force;
            universe.forces[j] = universe.forces[j] - force;
        }
    }
}

void NaiveSequentialSimulation::calculate_velocities(Universe& universe)
{
    // Iterate over each body in the universe to update its velocity
    for (std::uint32_t i = 0; i < universe.num_bodies; ++i) {
        // Calculate acceleration using Newton's second law: a = F / m
        Vector2d<double> acceleration = universe.forces[i] / universe.weights[i];

        // Calculate the new velocity: v' = v_0 + a * t
        Vector2d<double> new_velocity = universe.velocities[i] + acceleration * epoch_in_seconds;

        // Update the velocity in the universe
        universe.velocities[i] = new_velocity;
    }
}

void NaiveSequentialSimulation::calculate_positions(Universe& universe) {
    // Loop over each body in the universe
    for (std::uint32_t i = 0; i < universe.num_bodies; ++i) {
        // Calculate displacement: s = v * t
        Vector2d<double> displacement = universe.velocities[i] * epoch_in_seconds;

        // Update the position: p' = p0 + s
        universe.positions[i] = universe.positions[i] + displacement;
    }
}

void NaiveSequentialSimulation::simulate_epoch(Plotter& plotter, Universe& universe, bool create_intermediate_plots, std::uint32_t plot_intermediate_epochs) {
    // Step 1: Update the forces
    calculate_forces(universe);

    // Step 2: Update the velocities
    calculate_velocities(universe);

    // Step 3: Update the positions
    calculate_positions(universe);

    // Step 4: Increment the epoch counter
    universe.current_simulation_epoch++;

    // Step 5: Generate a system plot if conditions are met
    if (create_intermediate_plots && universe.current_simulation_epoch % plot_intermediate_epochs == 0) {
        plotter.add_bodies_to_image(universe);
        plotter.write_and_clear(); // Saves and resets the plot image
    }
}

void NaiveSequentialSimulation::simulate_epochs(Plotter& plotter, Universe& universe, std::uint32_t num_epochs, bool create_intermediate_plots, std::uint32_t plot_intermediate_epochs) {
    // Loop through the number of epochs to simulate
    for (std::uint32_t epoch = 0; epoch < num_epochs; ++epoch) {
        simulate_epoch(plotter, universe, create_intermediate_plots, plot_intermediate_epochs);
    }
}




