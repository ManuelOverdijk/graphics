/* Computer Graphics, Assignment 4, Positioning the camera
 *
 * Filename ........ lookat.c
 * Description ..... Contains the re-programmed lookAt function
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
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>

 
/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

void normalize(GLfloat *a)
{
    int i = 0;
    GLfloat len = sqrt(inProduct(a, a));
    for(; i < 3; i++)
    {
        a[i] /= len;
    }
}


void myLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
              GLdouble centerX, GLdouble centerY, GLdouble centerZ,
              GLdouble upX, GLdouble upY, GLdouble upZ) {

	GLdouble cz[3]
	cz[0] = eyeX - centerX;
	cz[1] = eyeY - centerY;
	cz[2] = eyeZ - centerZ;


	normalize(cz);

	
}
