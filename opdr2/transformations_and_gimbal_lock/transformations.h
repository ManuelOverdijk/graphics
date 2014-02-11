/* Computer Graphics, Assignment, Translations, Rotations and Scaling
 *
 * Filename ........ transformations.h
 * Description ..... Contains the re-programmed translation, rotation and scaling functions
 *
 */

#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H


void myScalef(GLfloat x, GLfloat y, GLfloat z);
void myTranslatef(GLfloat x, GLfloat y, GLfloat z);
void myRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void crossProduct(GLfloat a[3], GLfloat b[3], GLfloat *out);
GLfloat inProduct(GLfloat a[3], GLfloat b[3]);
void normalize(GLfloat *a);


#endif
