/* Computer Graphics, Assignment, Bezier curves
 * Filename ........ bezier.c
 * Description ..... Bezier curves
 * Date ............ 22.07.2009
 * Created by ...... Paul Melis
 *
 * Student name: Manuel Overdijk & Youp Uylings
 * Student email: manuel.overdijk@gmail.com, juylings@hotmail.com
 * Collegekaart: 10374582, 6129536
 * Date: 18/02/2014
 * Comments: ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <math.h>
#include "bezier.h"
#include <stdio.h>

/* Given a Bezier curve defined by the 'num_points' control points
 * in 'p' compute the position of the point on the curve for parameter
 * value 'u'.
 *
 * Return the x and y values of the point by setting *x and *y,
 * respectively.
 */


GLfloat bern_poly(GLint n, GLint k, GLfloat u) {
	/* first calculated the binomial distribution */
	int nk = n - k;

	/* n! */
    GLint value_n = 1;
    for (GLint i = 2; i <= n; i++) {
        value_n *= i;}

    /* k! */
    GLint value_k = 1;    
    for (GLint i = 2; i <= k; i++) {
    value_k *= i;}

    /* ( n - k ) ! */
    GLint n_min_k = 1;    
    for (GLint i = 2; i <= nk; i++) {
    n_min_k *= i;}

    /* calculated binominal distribution */
    GLfloat binomial_distribution = value_n / ((GLfloat) value_k * n_min_k);
	/* calculated the ith Bernstein polynomial of degree n */
    return binomial_distribution * pow(u, k) * pow(1 - u, n - k);
}

void
evaluate_bezier_curve(GLfloat *x, GLfloat *y, control_point p[], GLint num_points, GLfloat u)
{
	/* initializing values */
    *x = 0.0;
    *y = 0.0;

    /*  
     * calculates a bezier curve P(u) of arbitrary degree n by multiplying the control ax-points
     * with the bernstein polynomial 
     */
    for (GLint i = 0; i < num_points; i++) {
        GLfloat bernstein = bern_poly(num_points - 1, i, u);
        *x += bernstein * p[i].x;
        *y += bernstein * p[i].y;
    }
}

/* Draw a Bezier curve defined by the control points in p[], which
 * will contain 'num_points' points.
 *
 * Draw the line segments you compute directly on the screen
 * as a single GL_LINE_STRIP. This is as simple as using
 *
 *      glBegin(GL_LINE_STRIP);
 *      glVertex2f(..., ...);
 *      ...
 *      glEnd();
 *
 * DO NOT SET ANY COLOR!
 *
 * The 'num_segments' parameter determines the "discretization" of the Bezier
 * curve and is the number of straight line segments that should be used
 * to approximate the curve.
 *
 * Call evaluate_bezier_curve() to compute the necessary points on
 * the curve.
 */

void
draw_bezier_curve(GLint num_segments, control_point p[], GLint num_points)
{

    GLfloat x, y;

    glBegin(GL_LINE_STRIP);

    // start line
    glVertex2f(p[0].x, p[0].y);

    // calculate and draw points in the middle
    for (GLint i = 1; i < num_segments; i++) {
        evaluate_bezier_curve(&x, &y, p, num_points, i / (GLfloat) num_segments);
        glVertex2f(x, y);
    }

    // end line
    glVertex2f(p[num_points - 1].x, p[num_points - 1].y);
    glEnd();

}

/* Find the intersection of a cubic Bezier curve with the line X=x.
   Return 1 if an intersection was found and place the corresponding y
   value in *y.
   Return 0 if no intersection exists.
*/

int
intersect_cubic_bezier_curve(float *y, control_point p[], float x)
{
    return 0;
}

