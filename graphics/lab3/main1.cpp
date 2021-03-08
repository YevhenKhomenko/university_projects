#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <math.h>
#define PI 3.14159265

GLfloat xAngle=0,yAngle=0,scale=1.0;
static double cx = 0., cy = 0., cz = 0.;
double  lightCoord = 0.0;

void moveCamera() {
    glMatrixMode(GL_MODELVIEW);
    cz=cos(yAngle/180 * PI);
    cx=sin(yAngle/180 * PI);
    gluLookAt(cx,cy,cz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void light()
{
    GLfloat light_ambient[] = {1, 0, 0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {(float) cos(lightCoord) * 100, (float) sin(lightCoord) * 100, 0.0, 0.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
}

void displayPicture(void)
{
    glColor3f(1,0,0);
    
    glPushMatrix();
    glTranslatef(3,0,3);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(3, 0, -3);
    glutSolidSphere(1,10,10);
    glPopMatrix();
    
    glColor3f(0,1,0);
    
    glPushMatrix();
    glTranslatef(-3, 0, -3);
    glutWireCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-3, 0, 3);
    glutWireSphere(1,10,10);
    glPopMatrix();
    
    glutSwapBuffers();
    glFinish();
}

void displayGraphic(void)
{
    GLdouble points[300];
    GLint count=0;
    for (GLint y=0;y<10;y++)
    {
        for (GLint x=0;x<10;x++)
        {
            points[count++]=x;
            points[count++]=y;
            points[count++]=sqrt(x*y);
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

void myInit(void)
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-10);
    //moveCamera();
    light();
    glRotatef(xAngle,1,0,0);
    glRotatef(yAngle,0,1,0);
    glScalef(scale,scale,scale);
    displayPicture();
    displayGraphic();
    
}

void reshapePicture(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,1,20);
    //glOrtho(-10.0, 10.0, -10.0, 10.0, -15., 15);
    glMatrixMode(GL_MODELVIEW);
}

void resizePicture(unsigned char key, int x,int y)
{
    switch(key)
    {
        case '+':
            scale+=0.2;
            break;
        case '-':
            if (scale-0.2>0)
                scale-=0.2;
            break;
    }
    glutPostRedisplay();
    
}

void movePicture(int key,int x,int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            xAngle+=5;
            break;
        case GLUT_KEY_DOWN:
            xAngle-=5;
            break;
        case GLUT_KEY_LEFT:
            yAngle+=5;
            break;
        case GLUT_KEY_RIGHT:
            yAngle-=5;
            break;
    }
    glutPostRedisplay();
}

void update (int value){
    
    xAngle += value;
    if (xAngle> 360) {
        xAngle -=360;
    }
    glutPostRedisplay();
    glutTimerFunc(40, update, value);
}

int main(int argc,char * argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(300,300);
    glutCreateWindow("laba");
    glutDisplayFunc(myInit);
    glutReshapeFunc(reshapePicture);
    glutKeyboardFunc(resizePicture);
    glutSpecialFunc(movePicture);
    glutTimerFunc(40, update, 2);
    glutMainLoop();
    return 0;
}





