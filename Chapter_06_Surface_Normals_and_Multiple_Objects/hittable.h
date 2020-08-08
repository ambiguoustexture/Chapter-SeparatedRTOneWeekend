#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    point3 p;
    // The second design decision for normals is whether they should always point out.
    vec3 normal;
    double t;
    
    // If we decide to have the normals always point out, 
    // then we will need to determine which side the ray is on when we color it. 

    // If so, we won't be able to use the dot product to determine 
    // which side of the surface the ray is on. 
    // Instead, we would need to store that information
    bool front_face;

    // We can figure this out by comparing the ray with the normal.
    // If the ray and the normal face in the same direction, the ray is inside the object,
    // if the ray and the normal face in the opposite direction, then the ray is outside the object.
    // This can be determined by taking the dot product of the two vectors,
    // where if their dot is positive, the ray is inside the sphere.
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
    public:
        // This hittable abstract class will have a hit function 
        // that takes in a ray. 
        // It`s convenient to add a valid interval for hits t_min to t_max, 
        // so the hit only “counts” if t_min < t < t_max
        virtual bool hit(const ray& r, double t_min, double t_max, 
                hit_record& rec) const = 0;
};

#endif
