/* Computer Graphics and Game Technology, Assignment Ray-tracing
 *
 * Student name ....
 * Student email ...
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"
#include "perlin.h"
#include "v3math.h"
#include "intersection.h"
#include "scene.h"
#include "quat.h"
#include "constants.h"

// shade_constant()
//
// Always return the same color. This shader does no real computations
// based on normal, light position, etc. As such, it merely creates
// a "silhouette" of an object.

float max(float a, float b);

/* berekend max waarde */
float max(float a, float b)
{
    if(a > b)
    {
      return a;
    }
    else
    {
      return b;
    }
}

vec3
shade_constant(intersection_point ip)
{
    return v3_create(1, 0, 0);
}

vec3
shade_matte(intersection_point ip)
{
    float intensity = 0.0;
    for(int i = 0; i < scene_num_lights; i++)
    {
        /* berekend vector Li, de richting naar lichtbron */
        vec3 Li = v3_normalize(v3_subtract(scene_lights[i].position,ip.p));

        /* the hoek van de lichtbron t.o.v. object */
        float dot_ipn_Li = v3_dotprod(ip.n, Li);

        /* kijkt of er schaduw is */
        if(!shadow_check(v3_add(ip.p, v3_multiply(ip.n, 0.001)), Li))
        {
            intensity += scene_lights[i].intensity * max(0, dot_ipn_Li);
        }
    }
    intensity = scene_ambient_light + intensity;
    return v3_create(intensity,intensity,intensity);
}

vec3
shade_blinn_phong(intersection_point ip)
{
    float intensity = 0.0, Ks = 0.5, Kd = 0.8, alpha = 50, phong = 0;
    vec3 cs = v3_create(1,1,1), cd = v3_create(1,0,0), halfway_point, shade_matte, phong_formula;
    for(int i = 0; i < scene_num_lights; i++)
    {
        /* berekend vector Li, de richting naar lichtbron */
        vec3 Li = v3_normalize(v3_subtract(scene_lights[i].position,ip.p));

        /* the hoek van de lichtbron t.o.v. object */
        float dot_ipn_Li = v3_dotprod(ip.n, Li);

        /* kijkt of er schaduw is */
        if(!shadow_check(v3_add(ip.p, v3_multiply(ip.n, 0.001)), Li))
        {
            intensity += scene_lights[i].intensity * max(0, dot_ipn_Li);
        }
        halfway_point = v3_normalize(v3_add(ip.i, Li));
        phong += scene_lights[i].intensity * pow(v3_dotprod(ip.n,halfway_point), alpha);
    }
    shade_matte = v3_multiply(cd, (Kd * intensity));
    phong_formula = v3_multiply(cs, (Ks * phong));
    return v3_add(shade_matte, phong_formula);
}

vec3
shade_reflection(intersection_point ip)
{
    return v3_create(1, 0, 0);
}

// Returns the shaded color for the given point to shade.
// Calls the relevant shading function based on the material index.
vec3
shade(intersection_point ip)
{
  switch (ip.material)
  {
    case 0:
      return shade_constant(ip);
    case 1:
      return shade_matte(ip);
    case 2:
      return shade_blinn_phong(ip);
    case 3:
      return shade_reflection(ip);
    default:
      return shade_constant(ip);

  }
}

// Determine the surface color for the first object intersected by
// the given ray, or return the scene background color when no
// intersection is found
vec3
ray_color(int level, vec3 ray_origin, vec3 ray_direction)
{
    intersection_point  ip;

    // If this ray has been reflected too many times, simply
    // return the background color.
    if (level >= 3)
        return scene_background_color;

    // Check if the ray intersects anything in the scene
    if (find_first_intersection(&ip, ray_origin, ray_direction))
    {
        // Shade the found intersection point
        ip.ray_level = level;
        return shade(ip);
    }

    // Nothing was hit, return background color
    return scene_background_color;
}
