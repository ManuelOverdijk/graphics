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

float f01(float x0,float x1,float y0,float y1,float x,float y)
{
	float f01;
	f01 = (y0 - y1) * x + (x1 - x0) * y + (x0*y1 - x1*y0);
	return f01;

}

float f12(float x1,float y1,float x2,float y2,float x,float y)
{
	float f12;
	f12 = (y1 - y2) * x + (x2 - x1) * y + (x1*y2 - x2*y1);
	return f12;

}

float f20(float x0,float y0,float x2,float y2,float x,float y)
{	
	float f20;
	f20 = (y2 - y0) * x + (x0 - x2) * y + (x2*y0 - x0*y2);
	return f20;
}

float min(float var1, float var2)
{
	if(var1 < var2)
	{
		return var1;
	}
	else
	{
		return var2;
	}
}

float max(float var1, float var2)
{
	if(var1 > var2)
	{
		return var1;
	}
	else
	{
		return var2;
	}
}


void
draw_triangle(float x0, float y0, float x1, float y1, float x2, float y2,
    byte r, byte g, byte b)
{

		float xmin, xtemp_min, xtemp_max, ytemp_min, ytemp_max, xmax, ymin, ymax, alpha, betha, epsilon, fa, fb, fj, x , y;
		byte red = r, green = g, blue = b;

		/*calculates the maximim and minumim values */
		xtemp_min = min(x0,x1);
		xmin = min(xtemp_min, x2);

		xtemp_max = max(x0, x1);
		xmax = max(xtemp_max, x2);

		ytemp_min = min(y0, y1);
		ymin = min(ytemp_min, y2);

		ytemp_max = max(y0, y1);
		ymax = max(ytemp_max, y2);

		fa = f12(x1, y1, x2, y2, x0, y0);
		fb = f20(x0, y0, x2, y2, x1, y1);
		fj = f01(x0, x1, y0, y1, x2, y2);

		for (y = ymin; ymin < ymax; y++)
		{
			for (x = xmin; xmin < xmax; x++)
			{
				alpha = (f12(x1, y1, x2, y2, x, y) / fa);
				betha = (f20(x0, y0, x2, y2, x, y) / fb);
				epsilon = (f01(x0, x1, y0, y1, x, y) / fj);
				if (alpha >= 0 && alpha >= 0 && epsilon >= 0)
				{
					if ((alpha > 0 || fa * f12(x1, y1, x2, y2, -1,-1) > 0) && (betha > 0 || fb * f20(x0, y0, x2, y2,-1,-1) > 0) && (epsilon > 0 || fj * f01(x0, x1, y0, y1,-1,-1) > 0))
					{	
						//colour = (alpha*red + betha*green + epsilon*blue);
					    PutPixel(x,y,red, green, blue);
					}
				}
			}
		}

}

void
draw_triangle_optimized(float x0, float y0, float x1, float y1, float x2, float y2,
    byte r, byte g, byte b)
{
}
