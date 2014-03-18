/* Computer Graphics, Assignment, Volume rendering with cubes/points/isosurface
 *
 * Student name ....
 * Student email ...
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "marching_tetrahedra.h"
#include <math.h>

/* Compute a linearly interpolated position where an isosurface cuts
   an edge between two vertices (p1 and p2), each with their own
   scalar value (v1 and v2) */

static vec3
interpolate_points(unsigned char isovalue, vec3 p1, vec3 p2, unsigned char v1, unsigned char v2)
{

  /* tries to interpolate the points */
  vec3 interpolate;

  /* End points */
  double interpolate_value1 = fabs(isovalue - v2) / fabs(v2 - v1);
  double interpolate_value2 = fabs(isovalue - v1) / fabs(v2 - v1);

  double interpolate_weight1 = interpolate_value1;
  double interpolate_weight2 = interpolate_value2;

  interpolate = v3_add(v3_multiply(p1, fabs(isovalue - v2) / fabs(v2 - v1)),
   v3_multiply(p2, fabs(isovalue - v1) / fabs(v2 - v1)));


  if(fabs(isovalue - v1) < fabs(isovalue - v2))
  {
       interpolate = v3_add(v3_multiply(p1, 0.75), v3_multiply(p2, 0.25));
  }
  else
  {
       interpolate = v3_add(v3_multiply(p1, 0.25), v3_multiply(p2, 0.75));

  }
    //interpolate = v3_add(v3_multiply(p1, 0.5), v3_multiply(p2, 0.5));

    return interpolate;
}

/* Using the given iso-value generate triangles for the tetrahedron
   defined by corner vertices v0, v1, v2, v3 of cell c.

   Store the resulting triangles in the "triangles" array.

   Return the number of triangles created (either 0, 1, or 2).

   Note: the output array "triangles" should have space for at least
         2 triangles.
*/

static int
generate_tetrahedron_triangles(triangle *triangles, unsigned char isovalue, cell c, int v0, int v1, int v2, int v3)
{
    /* draws the case 0001 1110 with help of the interpolation function*/
    if((c.value[v3] < isovalue && c.value[v2] < isovalue && c.value[v1] < isovalue && c.value[v0] > isovalue) 
      || (c.value[v3] > isovalue && c.value[v2] > isovalue && c.value[v1] > isovalue && c.value[v0] < isovalue))
    {
        vec3 v0_v1, v0_v3, v0_v2;

        /* calculates corner points of triangle with help of interpolate function */
        v0_v1 = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        v0_v3 = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);
        v0_v2 = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);

        triangles[0].p[0] = v0_v1;
        triangles[0].p[1] = v0_v3;
        triangles[0].p[2] = v0_v2;

        /* generates a bit of shading normalvector perpendicular on triangle */
        vec3 normalize = v3_normalize(v3_crossprod(v3_subtract(triangles[0].p[1], triangles[0].p[0]), 
        v3_subtract(triangles[0].p[2], triangles[0].p[0])));

        triangles[0].n[0] = normalize;
        triangles[0].n[1] = normalize;
        triangles[0].n[2] = normalize;

        return 1;
    }
    /* draws the case 0010 1101 */
    if((c.value[v0] < isovalue && c.value[v3] < isovalue && c.value[v2] < isovalue && c.value[v1] > isovalue) 
      || (c.value[v0] > isovalue && c.value[v3] > isovalue && c.value[v2] > isovalue && c.value[v1] < isovalue))
    {
        vec3 v0_v1, v1_v2, v1_v3;

        v0_v1 = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        v1_v2 = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        v1_v3 = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);

        triangles[0].p[0] = v0_v1;
        triangles[0].p[1] = v1_v2;
        triangles[0].p[2] = v1_v3;

        vec3 normalize = v3_normalize(v3_crossprod(v3_subtract(triangles[0].p[1], triangles[0].p[0]), 
        v3_subtract(triangles[0].p[2], triangles[0].p[0])));

        triangles[0].n[0] = normalize;
        triangles[0].n[1] = normalize;
        triangles[0].n[2] = normalize;

        return 1;
    }
    /* draws the case 0100 1011 */
    if((c.value[v3] < isovalue && c.value[v0] < isovalue && c.value[v1] < isovalue && c.value[v2] > isovalue) 
      || (c.value[v3] > isovalue && c.value[v0] > isovalue && c.value[v1] > isovalue && c.value[v2] < isovalue))
    {
        vec3 v0_v2, v1_v2, v2_v3;

        v0_v2 = interpolate_points(isovalue, c.p[v2], c.p[v0], c.value[v2], c.value[v0]);
        v1_v2 = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        v2_v3 = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);

        triangles[0].p[0] = v0_v2;
        triangles[0].p[1] = v1_v2;
        triangles[0].p[2] = v2_v3;

        vec3 normalize = v3_normalize(v3_crossprod(v3_subtract(triangles[0].p[1], triangles[0].p[0]), 
        v3_subtract(triangles[0].p[2], triangles[0].p[0])));

        triangles[0].n[0] = normalize;
        triangles[0].n[1] = normalize;
        triangles[0].n[2] = normalize;

        return 1;
    }
    /* draws the case 0100 0111 */
    if((c.value[v0] < isovalue && c.value[v1] < isovalue && c.value[v2] < isovalue && c.value[v3] > isovalue) 
      || (c.value[v0] > isovalue && c.value[v1] > isovalue && c.value[v2] > isovalue && c.value[v3] < isovalue))
    {

        vec3 v0_v3, v1_v3, v2_v3;

        v0_v3 = interpolate_points(isovalue, c.p[v3], c.p[v0], c.value[v3], c.value[v0]);
        v1_v3 = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);
        v2_v3 = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);

        triangles[0].p[0] = v0_v3;
        triangles[0].p[1] = v1_v3;
        triangles[0].p[2] = v2_v3;

        vec3 normalize = v3_normalize(v3_crossprod(v3_subtract(triangles[0].p[1], triangles[0].p[0]), 
        v3_subtract(triangles[0].p[2], triangles[0].p[0])));

        triangles[0].n[0] = normalize;
        triangles[0].n[1] = normalize;
        triangles[0].n[2] = normalize;

        return 1;
    }
    /* draws the case 0011 1100  */
    if((c.value[v2] < isovalue && c.value[v3] < isovalue && c.value[v0] > isovalue && c.value[v1] > isovalue) 
      || (c.value[v2] > isovalue && c.value[v3] > isovalue && c.value[v0] < isovalue && c.value[v1] < isovalue))
    {
        vec3 v0_v2, v0_v3, v1_v3, v1_v2;
        v0_v2 = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        v0_v3 = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);
        v1_v3 = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);
        v1_v2 = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);

        triangles[0].p[0] = v0_v3;
        triangles[0].p[1] = v0_v2;
        triangles[0].p[2] = v1_v3;

        vec3 normalize = v3_normalize(v3_crossprod(v3_subtract(triangles[0].p[1], triangles[0].p[0]), 
        v3_subtract(triangles[0].p[2], triangles[0].p[0])));

        triangles[0].n[0] = normalize;
        triangles[0].n[1] = normalize;
        triangles[0].n[2] = normalize;

        triangles[1].p[0] = v1_v3;
        triangles[1].p[1] = v1_v2;
        triangles[1].p[2] = v0_v2;

        vec3 normalize2 = v3_normalize(v3_crossprod(v3_subtract(triangles[1].p[1], triangles[1].p[0]), 
        v3_subtract(triangles[1].p[2], triangles[1].p[0])));

        triangles[1].n[0] = normalize2;
        triangles[1].n[1] = normalize2;
        triangles[1].n[2] = normalize2;

        return 2;
    }
    /* draws the case 0101 1010 */
    if((c.value[v3] < isovalue && c.value[v1] < isovalue && c.value[v2] > isovalue && c.value[v0] > isovalue) 
      || (c.value[v3] > isovalue && c.value[v1] > isovalue && c.value[v2] < isovalue && c.value[v0] < isovalue))
    {
        vec3 v0_v1, v0_v3, v1_v2, v3_v2;
        v0_v1 = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        v0_v3 = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);
        v1_v2 = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        v3_v2 = interpolate_points(isovalue, c.p[v3], c.p[v2], c.value[v3], c.value[v2]);
 
        triangles[0].p[0] = v0_v3;
        triangles[0].p[1] = v3_v2;
        triangles[0].p[2] = v1_v2;

        vec3 normalize = v3_normalize(v3_crossprod(v3_subtract(triangles[0].p[1], triangles[0].p[0]), 
        v3_subtract(triangles[0].p[2], triangles[0].p[0])));

        triangles[0].n[0] = normalize;
        triangles[0].n[1] = normalize;
        triangles[0].n[2] = normalize;

        triangles[1].p[0] = v0_v1;
        triangles[1].p[1] = v1_v2;
        triangles[1].p[2] = v0_v3;

        vec3 normalize2 = v3_normalize(v3_crossprod(v3_subtract(triangles[1].p[1], triangles[1].p[0]), 
        v3_subtract(triangles[1].p[2], triangles[1].p[0])));

        triangles[1].n[0] = normalize2;
        triangles[1].n[1] = normalize2;
        triangles[1].n[2] = normalize2;

        return 2;
    }
    /* draws the case 0110 1001 */
    if((c.value[v3] < isovalue && c.value[v0] < isovalue && c.value[v1] > isovalue && c.value[v2] > isovalue) 
      || (c.value[v3] > isovalue && c.value[v0] > isovalue && c.value[v1] < isovalue && c.value[v2] < isovalue))
    {
        vec3 v1_v3, v1_v0, v3_v2, v0_v2;
        v1_v3 = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[1], c.value[3]);
        v1_v0 = interpolate_points(isovalue, c.p[v1], c.p[v0], c.value[1], c.value[0]);
        v3_v2 = interpolate_points(isovalue, c.p[v3], c.p[v2], c.value[3], c.value[2]);
        v0_v2 = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[0], c.value[2]);

        triangles[0].p[0] = v3_v2;
        triangles[0].p[1] = v1_v3;
        triangles[0].p[2] = v0_v2;

        vec3 normalize = v3_normalize(v3_crossprod(v3_subtract(triangles[0].p[1], triangles[0].p[0]), 
        v3_subtract(triangles[0].p[2], triangles[0].p[0])));

        triangles[0].n[0] = normalize;
        triangles[0].n[1] = normalize;
        triangles[0].n[2] = normalize;

        triangles[1].p[0] = v1_v3;
        triangles[1].p[1] = v1_v0;
        triangles[1].p[2] = v0_v2;

        vec3 normalize2 = v3_normalize(v3_crossprod(v3_subtract(triangles[1].p[1], triangles[1].p[0]), 
        v3_subtract(triangles[1].p[2], triangles[1].p[0])));

        triangles[1].n[0] = normalize2;
        triangles[1].n[1] = normalize2;
        triangles[1].n[2] = normalize2;

        return 2;
    }

    return 0;
}

/* Generate triangles for a single cell for the given iso-value. This function
   should produce at most 6 * 2 triangles (for which the "triangles" array should
   have enough space).

   Use calls to generate_tetrahedron_triangles().

   Return the number of triangles produced
*/

int
generate_cell_triangles(triangle *triangles, cell c, unsigned char isovalue)
{
    /* creates all the tetrahedron cases */ 
    int nr_triangles = 0;
    nr_triangles += generate_tetrahedron_triangles(&triangles[nr_triangles], isovalue, c, 0, 1, 3, 7);
    nr_triangles += generate_tetrahedron_triangles(&triangles[nr_triangles], isovalue, c, 0, 2, 3, 7);
    nr_triangles += generate_tetrahedron_triangles(&triangles[nr_triangles], isovalue, c, 0, 1, 5, 7);
    nr_triangles += generate_tetrahedron_triangles(&triangles[nr_triangles], isovalue, c, 0, 2, 6, 7);
    nr_triangles += generate_tetrahedron_triangles(&triangles[nr_triangles], isovalue, c, 0, 4, 5, 7);
    nr_triangles += generate_tetrahedron_triangles(&triangles[nr_triangles], isovalue, c, 0, 4, 6, 7);

    return nr_triangles;
}
