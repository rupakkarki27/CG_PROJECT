#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>

extern bool gameStarted;
float handAngle = 110;
short handDir = 1;

void drawCharacter(float angle, float jumpOffset, float proneAngle, float shiftAngle) {
    if(handDir == 1 && handAngle > 50) {
        handAngle -= 3;
    }else if(handDir == -1 && handAngle < 110) {
        handAngle += 3;
    }
    if(handDir == 1 && handAngle <= 50) {
        handDir -= 1;
    }else if(handDir == -1 && handAngle >= 110){
        handDir = 1;
    }
    glPushMatrix();
    glTranslatef(0.0, jumpOffset, -2.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glRotated(shiftAngle, 0.0, 1.0, 1.0);
    glColor3f(0.0f, 0.5f, 1.0f);

    glTranslatef(0.0, 0.75, 0.0f);
    glRotatef(-proneAngle, 1.0, 0.0, 0.0);

    glutSolidSphere(0.77f, 20, 20);

    // Basic Animation
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0);
    glTranslatef(0.59, 0.4, 0.0);
    glRotatef(handAngle, 0.0, 1.0, 0.0);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 0.1, 0.1, 0.4, 20, 20);
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.5);
    glutSolidSphere(0.15, 10, 10);
    glTranslatef(0.0, 0.0, -0.5);

    glColor3f(0.0, 1.0, 1.0);
    glRotatef(-handAngle, 0.0, 1.0, 0.0);
    glTranslatef(-1.18, 0.0, 0.0);
    glRotatef(-handAngle, 0.0, 1.0, 0.0);
    gluCylinder(quadratic, 0.1, 0.1, 0.4, 20, 20);
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.5);
    glutSolidSphere(0.15, 10, 10);
    glPopMatrix();

    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    glColor3f(1.0f, 0.5f, 0.5f);
    glutSolidCone(0.08f, 0.5f, 10, 2);

    glPopMatrix();
}

float trackOffset = 0;

void drawScene(float offset) {

    glDisable(GL_LIGHTING);
    if(gameStarted)
        trackOffset += 0.4;
    if(trackOffset > 120)
        trackOffset = 0.0;
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, trackOffset);
    glTranslatef(offset, 0.0, 0.0);

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_QUADS);
    {
        glVertex3f(-0.7, 0, 10.0);
        glVertex3f(0.7, 0.0, 10.0);
        glVertex3f(0.7, 0, -100.0);
        glVertex3f(-0.7, 0.0, -100.0);
    }glEnd();

    glTranslatef(2.5, 0.0, 0.0);

    glBegin(GL_QUADS);
    {
        glVertex3f(-0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, -100.0);
        glVertex3f(-0.7, 0.0, -100.0);
    }glEnd();

    glTranslatef(-5.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    {
        glVertex3f(-0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, -100.0);
        glVertex3f(-0.7, 0.0, -100.0);
    }glEnd();

    glTranslatef(2.5, 0.0, -120.0);

    glBegin(GL_QUADS);
    {
        glVertex3f(-0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, -100.0);
        glVertex3f(-0.7, 0.0, -100.0);
    }glEnd();

    glTranslatef(2.5, 0.0, 0.0);
    glBegin(GL_QUADS);
    {
        glVertex3f(-0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, -100.0);
        glVertex3f(-0.7, 0.0, -100.0);
    }glEnd();
    
    glTranslatef(-5.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    {
        glVertex3f(-0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, 10.0);
        glVertex3f(0.7, 0.0, -100.0);
        glVertex3f(-0.7, 0.0, -100.0);
    }glEnd();

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void initCamera(){
    glTranslatef(0.0, -2.0, -7.0);
    glRotatef(20, 1.0, 0.0, 0.0);
}

void startRun(){
    
}