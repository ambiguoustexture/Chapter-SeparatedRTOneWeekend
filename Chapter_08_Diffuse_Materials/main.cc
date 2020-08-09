#include "rtweekend.h"

#include "vec3.h" 
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "ray.h"
#include "camera.h"

#include <iostream>

// color ray_color(const ray& r, const hittable& world) 
color ray_color(const ray& r, const hittable& world, int recursion_depth) 
{
    hit_record rec;
    
    // If we've exceeded the ray bounce limit, no more light is gathered
    if (recursion_depth <= 0) 
        return color(0, 0, 0);

    // if (world.hit(r, 0, infinity, rec)) {
    // There’s also a subtle bug in there. 
    // Some of the reflected rays hit the object 
    // they are reflecting off of not at exactly t = 0, 
    // but instead at t = −0.0000001 or t = 0.00000001 
    // or whatever floating point approximation the sphere intersector gives us.
    // So we need to ignore hits very near zero
    if (world.hit(r, 0.001, infinity, rec)) {
        // Then update the ray_color() function to use the new random direction generator
        // point3 target = rec.p + rec.normal + random_in_unit_sphere();
        // This random_unit_vector() is a drop-in replacement 
        // for the existing random_in_unit_sphere() function.
        // point3 target = rec.p + rec.normal + random_unit_vector();
        point3 target = rec.p + random_in_hemisphere(rec.normal);
        // Notice that the ray_color function is recursive. When will it stop recursing? 
        // When it fails to hit anything. In some cases, however, that may be a long time — 
        // long enough to blow the stack. 
        // To guard against that, let's limit the maximum recursion depth, 
        // returning no light contribution at the maximum depth
        
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, recursion_depth - 1);
        // return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() 
{

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 256;
    const int max_recursion_depth = 50;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    // auto viewport_height = 2.0;
    // auto viewport_width = aspect_ratio * viewport_height;
    // auto focal_length = 1.0;

    // auto origin = point3(0, 0, 0);
    // auto horizontal = vec3(viewport_width, 0, 0);
    // auto vertical = vec3(0, viewport_height, 0);
    // auto lower_left_corner 
    //      = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    camera cam;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // The rows are written out from top to bottom
    for (int j = image_height-1; j >= 0; --j) {
    
        // The pixels are written out in rows with pixels left to right
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // auto u = double(i) / (image_width  - 1);
            // auto v = double(j) / (image_height - 1);
            // ray r(origin, 
            //         lower_left_corner + u*horizontal + v*vertical - origin);
            // color pixel_color = ray_color(r, world);
            color pixel_color(0, 0, 0);
            for (int cnt = 0; cnt < samples_per_pixel; cnt++) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_recursion_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}
