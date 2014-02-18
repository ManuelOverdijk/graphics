/* Computer Graphics, Assignment 4, Positioning the camera
 *
 * Filename ........ lookat.c
 * Description ..... Contains the re-programmed lookAt function
 * Created by ...... Jurgen Sturm 
 * Student name Manuel Overdijk, Youp Uylings
 * Student email manuel.overdijk@gmail.com, juylings@hotmail.com
 * Collegekaart 10374582, 6129536
 * Date 14/02/2014
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

GLdouble inProduct(GLdouble a[3], GLdouble b[3])
{
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

void normalize(GLdouble *a)
{
    int i = 0;
    GLdouble len = sqrt(inProduct(a, a));
    for(; i < 3; i++)
    {
        a[i] /= len;
    }
}

void crossProduct(GLdouble a[3], GLdouble b[3], GLdouble *out)
{
        out[0] = a[1]*b[2]-a[2]*b[1];
        out[1] = a[2]*b[0]-a[0]*b[2];
        out[2] = a[0]*b[1]-a[1]*b[0];
}

void myLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
              GLdouble centerX, GLdouble centerY, GLdouble centerZ,
              GLdouble upX, GLdouble upY, GLdouble upZ) {

	GLdouble cz[3];
	cz[0] = centerX - eyeX;
	cz[1] = centerY - eyeY;
	cz[2] = centerZ - eyeZ;
	normalize(cz);

	GLdouble up[3];
	up[0] = upX;
	up[1] = upY;
	up[2] = upZ;
	// normalize(up);

	GLdouble cx[3];
	crossProduct(cz,up,cx);
	normalize(cx);

	GLdouble cy[3];
	crossProduct(cx,cz,cy);
	// normalize(cy);	

    GLdouble RT[16] =
    {
        cx[0], cy[0], -cz[0], 0.0,
        cx[1], cy[1], -cz[1], 0.0,
        cx[2], cy[2], -cz[2], 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixd(RT);
}
