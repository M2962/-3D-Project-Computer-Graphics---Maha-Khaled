#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>


float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0, direction = 0.0;
float xPosCloud=-5, yPosSun=-5, xPosSun=-5, xPosTree=-1, yPosTree = -1;


void keydirect(int key, int x, int y){

    if (key == GLUT_KEY_LEFT) direction-=1;
    else if(key==GLUT_KEY_RIGHT) direction+=1;
}

void reshapeFunc (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (40.0, (GLdouble)w / (GLdouble)h, 0.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}
//animation timer
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
    if(xPosCloud<40){
    xPosCloud+=0.05;}
    if(xPosSun<40 && yPosSun<5){
    xPosSun+=0.05;
    yPosSun+=0.05;}
    if(xPosTree<0 && yPosTree<0.5){
        xPosTree+=0.01;
        yPosTree+=0.01;
    }

}

void car (){

    glBegin(GL_QUADS);

    //left side of car
    glColor3f(0,0,2);
    glVertex3f(0,5,0); //top left
    glVertex3f(0,0,0); // bottom left
    glVertex3f(30,0,0); // bottom right
    glVertex3f(30,5,0); // top right
    //right side of car
    glColor3f(0,0,2);
    glVertex3f(0,5,-10);
    glVertex3f(0,0,-10);
    glVertex3f(30,0,-10);
    glVertex3f(30,5,-10);
    //front of car
    glColor3f(0,0,2);
    glVertex3f(0,5,0); //top right with respect to car facing me
    glVertex3f(0,0,0); //bottom right
    glVertex3f(0,0,-10); //bottom left
    glVertex3f(0,5,-10); //top left
    //back of car
    glColor3f(0,0,2);
    glVertex3f(30,5,0);
    glVertex3f(30,0,0);
    glVertex3f(30,0,-10);
    glVertex3f(30,5,-10);

    //bottom of car
    glColor3f(0,0,2);
    glVertex3f(0,0,0); //front bottom left
    glVertex3f(0,0,-10);
    glVertex3f(30,0,-10); //back bottom left
    glVertex3f(30,0,0);


    glColor3f(0,0,2);
    glVertex3f(0,5,0);
    glVertex3f(0,5,-10);
    glVertex3f(30,5,-10);
    glVertex3f(30,5,0);


    //top part of car left
    glColor3f(0,0,2);
    glVertex3f(10,10,0); //top left
    glVertex3f(5,5,0); // bottom left
    glVertex3f(25,5,0); // bottom right
    glVertex3f(20,10,0); // top right

    //top part of car right
    glColor3f(0,0,2);
    glVertex3f(10,10,-10); //top left
    glVertex3f(5,5,-10); // bottom left
    glVertex3f(25,5,-10); // bottom right
    glVertex3f(20,10,-10); // top right



    //top part of car top
    glColor3f(0,0,2);
    glVertex3f(10,10,0); //top left
    glVertex3f(10,10,-10); // bottom left
    glVertex3f(20,10,-10); // bottom right
    glVertex3f(20,10,0); // top right

    //top part of car back
    glColor3f(0,10,5);
    glVertex3f(5,5,0); //top left
    glVertex3f(5,5,-10); // bottom left
    glVertex3f(10,10,-10); // bottom right
    glVertex3f(10,10,-0); // top right

    //top part of car front
    glColor3f(0,10,5);
    glVertex3f(20,10,0); //top left
    glVertex3f(20,10,-10); // bottom left
    glVertex3f(25,5,-10); // bottom right
    glVertex3f(25,5,-0); // top right

    glEnd();

    //wheels
    glColor3f(0,0,0);

    glPushMatrix();
    glTranslatef(5,0,0);
    glutSolidTorus(0.75,1.5,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,-10);
    glutSolidTorus(0.75,1.5,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25,0,0);
    glutSolidTorus(0.75,1.5,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25,0,-10);
    glutSolidTorus(0.75,1.5,30,30);
    glPopMatrix();

}

void sun(){
    glColor3f(2,3,0);
    glPushMatrix();
    glutSolidSphere(5,20,20);
    glPopMatrix();
}

void tree(){
    //Tree leaves
    glRotatef(90,0,0,20);
    glRotatef(90,0,20,0);
    glColor3f(0,1,0);
    glPushMatrix();
    glTranslatef(0+xPosTree, 3+yPosTree, 7);
    glutSolidCone(5,15,20,20);
    glPopMatrix();
    glRotatef(-90,0,20,0);
    glRotatef(-90,0,0,20);

    //Tree Log
    glRotatef(90,0,0,20);
    glRotatef(90,0,20,0);
    glColor3f(0.55,0.30,0);
    glPushMatrix();
    glTranslatef(0,3,0);
    GLUquadric *p = gluNewQuadric();
    gluQuadricDrawStyle(p,GLU_LINE);
    gluCylinder(p,1,1,10,90,90);
    glPopMatrix();
    glRotatef(-90,0,20,0);
    glRotatef(-90,0,0,20);
}

void cloud(){
    glColor3f(1,1,1);
    glPushMatrix();

    glutSolidSphere(5,20,20);
    glTranslatef(-2, -2, 0);
    glutSolidSphere(5,20,20);
    glTranslatef(4,0, 0);
    glutSolidSphere(5,20,20);
    glPopMatrix();
}

void display (void)
{
    glClearColor(0.67,0.84,0.90,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.2,0.2,0.2);
    glPushMatrix();
    glTranslatef(0,-58,0);
    glutSolidCube(100);
    glPopMatrix();

    //glRotatef(0.01,1,1,0);
    glPushMatrix();
    glTranslatef(direction,-5,10);
    car();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40+xPosSun, 40+yPosSun, 0);
    sun();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-5,-7,-7);
    tree();
    glTranslatef(-10,0,0);
    tree();
    glTranslatef(-10,0,0);
    tree();
    glTranslatef(-10,0,0);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(10+xPosCloud,40, 0);
    cloud();
    glPopMatrix();




    glFlush();
    glutSwapBuffers();

}

void idleFunc (void)
{
    zRotated += 1;
    glutPostRedisplay();
}

void texture (void){

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // buffer mode
    glutInitWindowSize(800, 700);
    glutInitWindowPosition (700, 200);
    glutCreateWindow("20101086");
    glEnable (GL_DEPTH_TEST);
    glutDisplayFunc (display);
    glutTimerFunc(1000, timer, 0);
    glutSpecialFunc(keydirect);
    glOrtho(-50,50,-50,50,-50,50);
    glRotatef(1,1,0,0);
    glClearColor (1.0, 1.0, 1.0, 0.0);

//    glutReshapeFunc (reshapeFunc);
    glutIdleFunc    (idleFunc);

    glClearColor(1,1,1,1);
    texture(); // Lighting and textures


    glutMainLoop();
}
