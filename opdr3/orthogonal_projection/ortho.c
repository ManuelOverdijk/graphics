/* Computer Graphics, Assignment 5, Orthogonal projection
 *
 * Filename ........ ortho.c
 * Description ..... Contains the re-programmed orthogonal projection matrix
 * Date ............ 01.09.2006
 * Created by ...... Jurgen Sturm 
 *
 * Student name .... Manuel Overdijk & Youp Uylings	
 * Student email ... manuel.overdijk@gmail.com & juylings@hotmail.com
 * Collegekaart .... 10374582 & 6129536
 * Date ............ 18 Feb 2014
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>

 
#define sqr(x) ((x)*(x))

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

/* Youp See  https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml */
void myOrtho(GLdouble left,
             GLdouble right,
             GLdouble bottom,
             GLdouble top,
             GLdouble near,
             GLdouble far) {

<<<<<<< HEAD
/* left, right
Specify the coordinates for the left and right vertical clipping planes. */

/* bottom, top
Specify the coordinates for the bottom and top horizontal clipping planes. */

/* nearVal, farVal
Specify the distances to the nearer and farther depth clipping planes. These values are negative if the plane is to be behind the viewer. */

//GLdouble 
=======
GLdouble M[16] = {
    2.0 / (right - left) , 0 , 0 , 0,
    0 , 2.0 / (top - bottom) , 0 , 0,
    0 , 0 ,  2.0 / (near - far)  , 0,
    -(right+left)/(right-left), -(top+bottom)/(top-bottom), -(near+far)
        /(near-far), 1
};
>>>>>>> d1423ffcdd89360b9190e58276d1047babae32db

glMultMatrixd(&M[0]);

}
