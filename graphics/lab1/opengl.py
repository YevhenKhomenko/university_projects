from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys


Width = 300
Height = 300
CubeSize = 37
keyStates = {}
movingForward = False
movingBackwards = False
x_move = 0.25 
y_move = -1


def Display():

    left  = (Width - CubeSize) / 2
    right = left + CubeSize
    bottom = (Height - CubeSize) / 2
    top = bottom + CubeSize

    5
    #glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
    
    glColor3ub(0,128,255)

    #print(movingForward)
    #print(movingBackwards)
    if movingForward:
        glTranslate(x_move, y_move, 0)
        print('moving forward')
    if movingBackwards:
        glTranslate(-x_move, -y_move, 0)
        print('moving backwards')


    glBegin(GL_QUADS)
    glVertex2f(left-40,bottom+40)
    glVertex2f(left-40,top+40)
    glVertex2f(right-40,top+40)
    glVertex2f(right-40,bottom+40)
    glEnd()
    glBegin(GL_QUADS)
    glVertex2f(right-40,top+40)
    glVertex2f(right-10,top+70)
    glVertex2f(right+40,top+70)
    glVertex2f(right+10,top+40)
    glEnd()

    glBegin(GL_TRIANGLE_STRIP)
    glVertex2f(right-40,bottom+40)
    glVertex2f(right+40,bottom-30)
    glVertex2f(right-40,bottom-30)
    glVertex2f(right+40,bottom-100)
    glEnd()

    glBegin(GL_TRIANGLE_STRIP)
    glVertex2f(right+40,bottom-100)
    glVertex2f(right-40,bottom-100)
    glVertex2f(right,bottom-65)
    glVertex2f(right-40,bottom-65)
    glEnd()

    glBegin(GL_TRIANGLES)
    glVertex2f(right-40,bottom-5)
    glVertex2f(left-30,bottom-30)
    glVertex2f(right-40,bottom-55)
    glEnd()

    glColor3ub(0,0,0)

    glBegin(GL_LINE_LOOP)
    glVertex2f(right-40,bottom+40)
    glVertex2f(left-40,bottom+40)
    glVertex2f(left-40,top+40)
    glVertex2f(right-40,top+40)
    glVertex2f(right-40,top+40)
    glVertex2f(right-10,top+70)
    glVertex2f(right+40,top+70)
    glVertex2f(right+10,top+40)
    glVertex2f(right-40,top+40)
    glVertex2f(right-40,bottom+40)
    glVertex2f(right-40,bottom+40)
    glVertex2f(right+40,bottom-30)
    glVertex2f(right+40,bottom-100)
    glVertex2f(right+40,bottom-100)
    glVertex2f(right-40,bottom-100)
    glVertex2f(right-40,bottom-65)
    glVertex2f(right,bottom-65)
    glVertex2f(right-40,bottom-30)
    glVertex2f(right-40,bottom-5)
    glVertex2f(left-30,bottom-30)
    glVertex2f(right-40,bottom-55)
    glVertex2f(right-40,bottom+40)
    glEnd()


    glFinish()



def Reshape(w, h):
    Width = w
    Height = h

    glViewport(0, 0, w, h)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity();


def keyPressed(key,x,y):  
    #print("key pressed")
    #print(key)
    #print(type(key))
    if key == b'q':
        global movingForward
        movingForward = True
        Display()
    if key == b'a':
        global movingBackwards
        movingBackwards = True
        Display()
    if key == b' ':
            sys.exit(0)


  
def keyUp (key,x,y) :
    if key == b'q':
        global movingForward
        movingForward = False
    if key == b'a':
        global movingBackwards
        movingBackwards = False
  
def main():

    glutInit(sys.argv);						
    glutInitDisplayMode(GLUT_RGB)				
    glutInitWindowSize(Width, Height)
    glutCreateWindow("LAB_1")

    glutDisplayFunc(Display)
    glutReshapeFunc(Reshape)
    glutKeyboardFunc(keyPressed)
    glutKeyboardUpFunc(keyUp)


    glutMainLoop();



main()
