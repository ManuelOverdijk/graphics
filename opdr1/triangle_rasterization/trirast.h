#ifndef TRIRAST_H
#define TRIRAST_H

#include "types.h"

void    draw_triangle(float x0, float y0, float x1, float y1,
            float x2, float y2, byte r, byte g, byte b);
void    draw_triangle_optimized(float x0, float y0, float x1, float y1,
            float x2, float y2, byte r, byte g, byte b);

// float f01(float x0,float x1,float y0,float y1,float x,float y);
// float f12(float x1,float y1,float x2,float y2,float x,float y);
// float f20(float x0,float y0,float x2,float y2,float x,float y);
// float min(float var1, float var2);
// float max(float var1, float var2);




#endif

