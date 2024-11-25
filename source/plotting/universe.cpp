#include "plotting/plotter.h"

void Plotter::highlight_position(Vector2d<double> position, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    // Check if the position is within the bounding box of the plot
    if (!plot_bounding_box.contains(position)) {
        return; // Do nothing if the position is outside the bounding box
    }

    // Convert position to pixel coordinates
    uint32_t x = static_cast<uint32_t>((position[0] - plot_bounding_box.x_min) / (plot_bounding_box.x_max - plot_bounding_box.x_min) * plot_width);
    uint32_t y = static_cast<uint32_t>((position[1] - plot_bounding_box.y_min) / (plot_bounding_box.y_max - plot_bounding_box.y_min) * plot_height);

    // Set horizontal and vertical lines (cross) centered at (x, y)
    for (int i = 0; i < plot_width; ++i) {
        mark_pixel(i, y, red, green, blue);  // Horizontal line
    }
    for (int i = 0; i < plot_height; ++i) {
        mark_pixel(x, i, red, green, blue);  // Vertical line
    }
}

void Plotter::add_bodies_to_image(Universe& universe) {
    // Loop over all bodies in the universe
    for (std::size_t i = 0; i < universe.num_bodies; ++i) {
        Vector2d<double> position = universe.positions[i];

        // Check if the body is within the bounding box of the plot
        if (!plot_bounding_box.contains(position)) {
            continue;  // Skip the body if it's outside the bounding box
        }

        // Convert body position to pixel coordinates
        uint32_t x = static_cast<uint32_t>((position[0] - plot_bounding_box.x_min) / (plot_bounding_box.x_max - plot_bounding_box.x_min) * plot_width);
        uint32_t y = static_cast<uint32_t>((position[1] - plot_bounding_box.y_min) / (plot_bounding_box.y_max - plot_bounding_box.y_min) * plot_height);

        // Mark the pixel at the body's position with white color (R: 255, G: 255, B: 255)
        mark_pixel(x, y, 255, 255, 255);
    }
}