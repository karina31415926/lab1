#include "plotting/plotter.h"
#include "io/image_parser.h"
#include <iostream>
#include <exception>

void Plotter::write_and_clear(){
    // create plot serial number string
    std::string serial_number_string = std::to_string(image_serial_number);
    while(serial_number_string.length() < 9){
        serial_number_string = "0" + serial_number_string;
    }

    std::string file_name = filename_prefix + "_" + serial_number_string + ".bmp";
    ImageParser::write_bitmap(output_folder_path / file_name, image);
    std::cout << "Current image serial number: " << image_serial_number << std::endl;
    std::cout << "Saving image to: " << filename_prefix + "_" + serial_number_string + ".bmp" << std::endl;
    clear_image();
    image_serial_number += 1;
}

BitmapImage::BitmapPixel Plotter::get_pixel(std::uint32_t x, std::uint32_t y){
    return image.get_pixel(y, x);
}

void Plotter::mark_pixel(std::uint32_t x, std::uint32_t y, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    // Check if the coordinates are within bounds
    if (x >= plot_width || y >= plot_height) {
        throw std::out_of_range("Pixel coordinates are out of bounds.");
    }

    // Set the pixel in the bitmap image
    image.set_pixel(x, y, BitmapImage::BitmapPixel(red, green, blue));
}

void Plotter::mark_position(Vector2d<double> position, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    // Check if the position is within the bounding box of the plot
    if (!plot_bounding_box.contains(position)) {
        return; // Do nothing if the position is outside the bounding box
    }

    // Convert position to pixel coordinates (assumption: scaling from universe to image space)
    uint32_t x = static_cast<uint32_t>((position[0] - plot_bounding_box.x_min) / (plot_bounding_box.x_max - plot_bounding_box.x_min) * plot_width);
    uint32_t y = static_cast<uint32_t>((position[1] - plot_bounding_box.y_min) / (plot_bounding_box.y_max - plot_bounding_box.y_min) * plot_height);

    // Set the pixel in the bitmap image
    mark_pixel(x, y, red, green, blue);
}

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