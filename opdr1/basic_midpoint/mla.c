/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.c
 * Description ..... Midpoint Line Algorithm
 * Created by ...... Jurgen Sturm 
 *
 * Student name .... Manuel Overdijk & Youp Uylings
 * Student email ... manuel.overdijk@gmail.com & juylings@hotmail.com
 * Collegekaart .... 10374582 & 6129536
 * Date ............ 07 Feb 2014
 * Comments ........ None
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include "SDL.h"   
#include "init.h"

/*
 * Midpoint Line Algorithm
 *
 * As you probably will have figured out, this is the part where you prove
 * your programming skills. The code in the mla function should draw a direct 
 * line between (x0,y0) and (x1,y1) in the specified color. 
 * 
 * Until now, the example code below draws only a horizontal line between
 * (x0,y0) and (x1,y0) and a vertical line between (x1,y1).
 * 
 * And here the challenge begins..
 *
 * Good luck!
 *
 *
 */



 /* Youp Uylings & Manuel Overdijk
  * Based on algorithm at http://en.wikipedia.org/wiki/Bresenham's_line_algorithm
  * and http://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html (larger and better explanation than the wiki article)
  *
  * 07 Feb 2014
  */
void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour) {
	int short_projection, long_projection, error, width, height, dx1, dy1, dx2, dy2;

	// Point (X0, Y0) to Point (X1, Y1)

	/* Width of the line to be drawn */
	width = x1 - x0;

	/* Height of the line  to be drawn */
	height = y1 - y0;

	dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;

	/* Quadrants for x < 0 */
	if (width < 0) {
		dx1 = -1;
		dx2 = -1;
	/* Quadrants for x > 0 */
	}  else {
		dx1 = 1;
		dx2 = 1;
	}

	/* Quadrants for y < 0 */
	if (height < 0) {
		/* Quadrant above y */
		dy1 = -1;
	} else {
		/* quadrants below y, mirroring y */
		dy1 = 1;
	}

	long_projection = abs(width);
	short_projection = abs(height);


	/* vertical projection is larger than horizontal projection, switch it up! */
	if (long_projection < short_projection) {
		/* Switch up long_projection and short_projection */
		int temp = long_projection;
		long_projection = short_projection;
		short_projection = temp;

	    if (height < 0) {
	    	dy2 = -1;
	    } else {
	    	dy2 = 1;
	    }

	    dx2 = 0;            
	}

	error = long_projection / 2;

	/* The actual drawing of the line */
	for (int j=0; j <= long_projection; j++) {

		//Draw pixel 
	    PutPixel(s,x0,y0,colour);

	    /* Increase error by the length of x1-x0 (depends on the quadrant
	     * if the error becomes bigger than the length of x1-x0, decrease by error by this length. 
		 * and up y with one (depends on the quadrant)
	     */
	    error += short_projection;
	    if (error >= long_projection) {
	        error -= long_projection;
	        x0 += dx1;
	        y0 += dy1;
	    } else {
	        x0 += dx2;
	        y0 += dy2;
	    }
	}
  return;
}

