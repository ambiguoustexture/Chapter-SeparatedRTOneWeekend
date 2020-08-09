#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
// There is no standard portable definition of pi, 
// so just define our own constant for it. 
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Clamps the value x to the range [min,max]
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// The “less than” before the 1 is important 
// as we will sometimes take advantage of that
inline double random_double() {
    // Returns a random real in [0,1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Return a random real in [min,max)
    return min + (max - min) * random_double();
}

// Common Headers

#include "ray.h"
#include "vec3.h"

#endif
