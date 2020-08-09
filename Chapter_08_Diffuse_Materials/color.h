#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "rtweekend.h"

#include <iostream>

// void write_color(std::ostream &out, color pixel_color) {
void write_color(std::ostream & out, color pixel_color, int samples_per_pixel) {
    // Write the translated [0,255] value of each color component.
    // out << static_cast<int>(255.999 * pixel_color.x()) << ' '
    //     << static_cast<int>(255.999 * pixel_color.y()) << ' '
    //     << static_cast<int>(255.999 * pixel_color.z()) << '\n';

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // // Divide the color by the number of samples 
    // auto scale = 1.0 / samples_per_pixel;
    // r *= scale;
    // g *= scale;
    // b *= scale;

    // These spheres should look pretty light (in real life, a light grey). 
    // The reason for this is that almost all image viewers assume 
    // that the image is “gamma corrected”, 
    // meaning the 0 to 1 values have some transform before being stored as a byte. 
    // There are many good reasons for that, but for our purposes we just need to be aware of it. 
    // To a first approximation, we can use “gamma 2” which means raising the color to the power
    
    // Divide the color by the number of samples and gamma-correct for gamma=2.0
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
