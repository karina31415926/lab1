#include "plotting/plotter.h"
#include "io/image_parser.h"
#include <exception>
#include <stdexcept>
#include <iostream>

void Plotter::write_and_clear(){
    // create plot serial number string
    std::string serial_number_string = std::to_string(image_serial_number);
    while(serial_number_string.length() < 9){
        serial_number_string = "0" + serial_number_string;
    }

    std::string file_name = filename_prefix + "_" + serial_number_string + ".bmp";
    ImageParser::write_bitmap(output_folder_path / file_name, image);

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
    image.set_pixel(y, x, BitmapImage::BitmapPixel(red, green, blue));
}

void Plotter::mark_position(Vector2d<double> position, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    // Check if the position is within the bounding box of the plot
    if (!plot_bounding_box.contains(position)) {
        return; // Do nothing if the position is outside the bounding box
    }

    // Convert position to pixel coordinates (assumption: scaling from universe to image space)
    uint32_t x = static_cast<uint32_t>((position[0] - plot_bounding_box.x_min) /
                                   (plot_bounding_box.x_max - plot_bounding_box.x_min) * (plot_width - 1));
    uint32_t y = static_cast<uint32_t>((position[1] - plot_bounding_box.y_min) /
                                   (plot_bounding_box.y_max - plot_bounding_box.y_min) * (plot_height - 1));

    // Set the pixel in the bitmap image
    mark_pixel(x, y, red, green, blue);
}