//
//  main.cpp
//  lab2
//
//  Created by Ievgen Khonenko on 11/18/19.
//  Copyright © 2019 Ievgen Khonenko. All rights reserved.
//

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#define PI 3.14159265
#define ESCAPE '\033'
#include <cmath>
#include <iostream>

float x = 0.5f, y = 0.5f, z;
static double cx = 0., cy = 0., cz = 0.;
double angleH = 45.0, angleV = 45.0;
double scaleCoef = 1;
double change_x, change_y, change_z = 0.;
double rotate_x, rotate_y, rotate_z = 0.;
double lightSpeed = 0.1, lightCoord = 0.0;

void ChangeCamera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cx = 100*cos(angleV * PI / 180.0) * cos(angleH * PI / 180.0);
    cz = 100*cos(angleV * PI / 180.0) * sin(angleH * PI / 180.0);
    cy = 100*sin(angleV * PI / 180.0) ;//+ 200;
    gluLookAt(cx, cy, cz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
}

void light() {
    GLfloat light_ambient[] = {1, 0, 0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightPosition[] = {(float) cos(lightCoord) * 100, (float) sin(lightCoord) * 100, 0.0, 0.0};
    
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glEnable(GL_NORMALIZE);
    lightCoord += lightSpeed;
}

void scale() {
    GLdouble scale_matrix[] = {
        scaleCoef, 0, 0, 0,
        0, scaleCoef, 0, 0,
        0, 0, scaleCoef, 0,
        0, 0, 0, 1};
    glMultMatrixd(scale_matrix);
}

void rotate() {
    GLdouble rotation_matrix_X[] = {
        1, 0, 0, 0,
        0, cos(rotate_x), sin(rotate_x), 0,
        0, -sin(rotate_x), cos(rotate_x), 0,
        0, 0, 0, 1};
    glMultMatrixd(rotation_matrix_X);
    
    GLdouble rotation_matrix_Y[] = {
        cos(rotate_y), 0, -sin(rotate_y), 0,
        0, 1, 0, 0,
        sin(rotate_y), 0, cos(rotate_y), 0,
        0, 0, 0, 1};
    glMultMatrixd(rotation_matrix_Y);
    
    GLdouble rotation_matrix_Z[] = {
        cos(rotate_z), sin(rotate_z), 0, 0,
        -sin(rotate_z), cos(rotate_z), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1};
    glMultMatrixd(rotation_matrix_Z);
}

void translate() {
    GLdouble translation_matrix_T[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        static_cast<GLdouble>(change_x),
        static_cast<GLdouble>(change_y), static_cast<GLdouble>(change_z), 1};
    glMultMatrixd(translation_matrix_T);
}


void draw_torus(void){
    
    glNewList(3, GL_COMPILE);
    glPushMatrix();
    
    glColor3ub(0, 0, 255);
    glTranslatef(100, 55, -50);
    glutSolidTorus(10, 20, 200, 200);
    
    glPopMatrix();
    glEndList();
    
    glNewList(4, GL_COMPILE);
    glPushMatrix();
    
    glColor3ub(255, 0, 255);
    glTranslatef(100, 55, -100);
    glutWireTorus(10, 20, 50, 50);
    
    glPopMatrix();
    glEndList();
    
}

void draw_cone(void){
    
    glNewList(1, GL_COMPILE);
    glPushMatrix();
    
    glColor3ub(255, 0, 0);
    glTranslatef(0, 0, -50);
    glutSolidCone(30, 50, 20, 20);
    
    glPopMatrix();
    glEndList();
    
    glNewList(2, GL_COMPILE);
    glPushMatrix();
    
    glColor3ub(0, 255, 0);
    glTranslatef(100, 55, 0);
    glutWireCone(30, 50, 20, 20);
    
    glPopMatrix();
    glEndList();
    
}

void draw_graph(void){
    
    GLdouble points[1200];
    GLint count=0;
    for (GLint y=0;y<20;y++)
    {
        for (GLint x=0;x<20;x++)
        {
            points[count++]=x * 3;
            points[count++]=y * 3;
            points[count++]= sin(x) * cos(y) * 3;
        }
    }
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1,0,0);
    glVertexPointer(3,GL_DOUBLE,0,points);
    glPushMatrix();
    glTranslatef(0,0,0);
    glDrawArrays(GL_POINTS,0,100);
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
    glFinish();
}



void display(void) {
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ChangeCamera();
    scale();
    translate();
    rotate();
    light();
    
    draw_torus();
    draw_cone();
    
    
    GLint list_of_lists[] = {1, 2, 3, 4};
    glCallLists(4, GL_INT, list_of_lists);
    
    glutSwapBuffers();
    glFinish();
    
    draw_graph();
}


void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-w / 2, w / 2, -h / 2, h / 2, -10000, 10000);
    glFrustum(-1,1,-1,1,1,10000);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    
    switch (key) {
        case ESCAPE:
            break;
        case '8':
            rotate_z += 1;
            break;
        case '7':
            rotate_x += 1;
            break;
        case '9':
            rotate_z += 1;
            break;
        case '0':
            change_x -= 2;
            break;
        case '1':
            change_x += 2;
            break;
        case '2':
            change_y -= 2;
            break;
        case '3':
            change_y += 2;
            break;
        case '6':
            scaleCoef -= 0.5;
            break;
        case '5':
            scaleCoef += 0.5;
            break;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
}

void specialKey(int key, int x, int y) {
    
    if (key == GLUT_KEY_RIGHT)
    {
        angleH += 5.0f;
    }
    if (key == GLUT_KEY_LEFT)
    {
        angleH -= 5.0f;
    }
    if (key == GLUT_KEY_UP)
    {
        if (angleV < 90.0)
            angleV += 5.0f;
    }
    if (key == GLUT_KEY_DOWN)
    {
        if (angleV > -90.0)
            angleV -= 5.0f;
    }
    
    glutPostRedisplay();
}

void update (int value){
    
    angleH += value;
    if (angleH> 360) {
        angleH -=360;
    }
    glutPostRedisplay();
    glutTimerFunc(40, update, 2);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Model");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutTimerFunc(40, update, 2);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
