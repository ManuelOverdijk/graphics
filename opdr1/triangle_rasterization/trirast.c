/* Computer Graphics assignment, Triangle Rasterization
 * Filename ........ trirast.c
 * Description ..... Implements triangle rasterization
 * Created by ...... Paul Melis
 *
 * Student name ....Manuel Overdijk & Youp Uylings
 * Student email ...manuel.overdijk@gmail.com & juylings@hotmail.com
 * Collegekaart ....10374582 & 6129536
 * Date ............ 06 Feb 2014
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "types.h"

/*
 * Rasterize a single triangle.
 * The triangle is specified by its corner coordinates
 * (x0,y0), (x1,y1) and (x2,y2).
 * The triangle is drawn in color (r,g,b).
 */
float highest(float a, float b, float c) {
    if (a > b && a > c)
        return a;
    if (b > c)
        return b;
    return c;
}

float lowest(float a, float b, float c) {
    if (a < b && a < c)
        return a;
    if (b < c)
        return b;
    return c;
}

float fij(float x, float y, float xi, float yi, float xj, float yj) {
    return (yi - yj)*x + (xj - xi)*y + xi*yj - xj*yi;
}


void draw_triangle(float x0, float y0, float x1, float y1, float x2, float y2,
        byte r, byte g, byte blue) {
    float xmin = floor(lowest(x0, x1, x2));
    float ymin = floor(lowest(y0, y1, y2));
    float xmax = floor(highest(x0, x1, x2));
    float ymax = floor(highest(y0, y1, y2));
    float fa = fij(x0, y0, x1, y1, x2, y2);
    float fb = fij(x1, y1, x2, y2, x0, y0);
    float fc = fij(x2, y2, x0, y0, x1, y1);
    for (float y = ymin; y <= ymax; y++) {
        for (float x = xmin; x <= xmax; x++) {
            float a = fij(x, y, x1, y1, x2, y2) / fa;
            float b = fij(x, y, x2, y2, x0, y0) / fb;
            float c = fij(x, y, x0, y0, x1, y1) / fc;
            if (a >= 0 && b >= 0 && c >= 0) {
                if ((a > 0 || fij(-1, -1, x1, y1, x2, y2) * fa > 0) &&
                        (b > 0 || fij(-1, -1, x2, y2, x0, y0) * fb > 0) &&
                        (c > 0 || fij(-1, -1, x0, y0, x1, y1) * fc > 0)) {
                    PutPixel(x, y, r, g, blue);
                }
            }
        }
    }

}

void draw_triangle_optimized(float x0, float y0, float x1, float y1, float x2,
        float y2, byte r, byte g, byte blue) {
    float xmin = floor(lowest(x0, x1, x2));
    float ymin = floor(lowest(y0, y1, y2));
    float xmax = floor(highest(x0, x1, x2));
    float ymax = floor(highest(y0, y1, y2));
    float fa = fij(x0, y0, x1, y1, x2, y2);
    float fb = fij(x1, y1, x2, y2, x0, y0);
    float fc = fij(x2, y2, x0, y0, x1, y1);
    float fa_outside = fij(-1, -1, x1, y1, x2, y2) * fa > 0;
    float fb_outside = fij(-1, -1, x2, y2, x0, y0) * fb > 0;
    float fc_outside = fij(-1, -1, x0, y0, x1, y1) * fc > 0;
    for (float y = ymin; y <= ymax; y++) {
        for (float x = xmin; x <= xmax; x++) {
            float a = fij(x, y, x1, y1, x2, y2) / fa;
            float b = fij(x, y, x2, y2, x0, y0) / fb;
            float c = fij(x, y, x0, y0, x1, y1) / fc;
            if (a >= 0 && b >= 0 && c >= 0 &&
                    (a > 0 || fa_outside) && (b > 0 || fb_outside) &&
                    (c > 0 || fc_outside)) {
                PutPixel(x, y, r, g, blue);
            }
        }
    }
}

