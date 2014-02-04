/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.c
 * Description ..... Midpoint Line Algorithm
 * Created by ...... Jurgen Sturm 
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
void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour) {
	int w = x1 - x0 ;
	int h = y1 - y0 ;
	int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
	if (w<0) dx1 = -1 ; else if (w>0) dx1 = 1 ;
	if (h<0) dy1 = -1 ; else if (h>0) dy1 = 1 ;
	if (w<0) dx2 = -1 ; else if (w>0) dx2 = 1 ;
	int longest = abs(w) ;
	int shortest = abs(h) ;
	if (!(longest>shortest)) {
	    longest = abs(h) ;
	    shortest = abs(w) ;
	    if (h<0) dy2 = -1 ; else if (h>0) dy2 = 1 ;
	    dx2 = 0 ;            
	}
	int numerator = longest >> 1 ;
	for (int i=0;i<=longest;i++) {
	    PutPixel(s,x0,y0,colour) ;
	    numerator += shortest ;
	    if (!(numerator<longest)) {
	        numerator -= longest ;
	        x0 += dx1 ;
	        y0 += dy1 ;
	    } else {
	        x0 += dx2 ;
	        y0 += dy2 ;
	    }
	}

    // int w = x1 - x0 ;
    // int h = y1 - y0;
    // double m = h/(double)w ;
    // double j = y0 ;
    // for (int i=x0;i<=x1;i++) {
    //     PutPixel(s,i,(int)j,colour);
    //     j += m ;
    // }

  return;
}

