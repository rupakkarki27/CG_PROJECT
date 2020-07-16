#include <GL/glut.h>
#include <iostream>
#include "game.h"

void display();
void reshape(int, int);
void keyboard(unsigned char, int, int);
void timer(int);


float rotAngle;
float characterOffset;
float jumpOffset; bool jumping; float jumpCounter;
float proneAngle; bool proning; int proneHold;
float shiftAngle; int shifting;
bool gameStarted = false;

int position;

void init()
{
    glEnable(GL_TEXTURE_2D);
    float lpos[] = {1.0, 3.0, 4.0};
    float lamb[] = {0.7, 0.7, 0.7, 1.0};
    float ldif[] = {1.0, 1.0, 1.0, 1.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lamb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ldif);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void startGame()
{
    gameStarted = true;
    rotAngle = 0, jumpOffset = 0, proneAngle = 0, shiftAngle = 0;
    characterOffset = 0;
    position = 0;
    jumping = false, proning = false;
}

int main(int argc, char**argv)
{

    std::cout<<"Starting Game...\nPress `Space` to start!!\n\nPress q to quit.\n";
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("Runner - Rupak | Sweekar");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000.0/60.0, timer, 0);
    glutMainLoop();
    return 0;
}

void initCharacter()
{
    if(rotAngle < 180)
        rotAngle += 2;
    if(rotAngle == 180)
        startRun();
    if(jumping)
    {
        jumpOffset = (3*jumpCounter) - (jumpCounter*jumpCounter);
        jumpCounter += 0.07;
        if(jumpOffset < 0){
            jumping = false;
            jumpCounter = 0;
            jumpOffset = 0;
        }
    }
    if(proning)
    {
        if(proneAngle <= 75.0)
            proneAngle += 5;
        else if(proneAngle > 75.0 && proneHold < 15)
            proneHold++;
        else
            proning = false;
        if(jumpCounter > 0.0)
        {
            if(jumpCounter < 1.5)
                jumpCounter = 3.0 - jumpCounter;
            jumpCounter += 0.2;
        }

    }
    else
    {
        if(proneAngle > 0.0)
            proneAngle -= 2.5;
        if(proneAngle <= 0.0)
        {
            proneHold = 0;
            proneAngle = 0.0;
        }
    }
    if(shifting == 1)
    {
        if(shiftAngle <= 25)
            shiftAngle++;
        else
            shifting = 0;
    }
    else if(shifting == -1)
    {
        if(shiftAngle >= -25)
            shiftAngle--;
        else
            shifting = 0;
    }
    else
    {
        if(shiftAngle > 0)
            shiftAngle -= 2;
        if(shiftAngle < 0)
            shiftAngle += 2;
    }
    if(position == 1 && characterOffset < 2.5)
        characterOffset += 0.15;
    else if(position == -1 && characterOffset > -2.5)
        characterOffset -= 0.15;
    else if(position == 0 && characterOffset < 0)
    {
        if(characterOffset > -0.15)
            characterOffset = 0.0;
        else
        characterOffset += 0.15;
    }
    else if(position == 0 && characterOffset > 0)
    {
        if(characterOffset < 0.15)
            characterOffset = 0.0;
        else
            characterOffset -= 0.15;
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    initCamera();
    drawScene(-characterOffset);
    if(gameStarted)
    {
        initCharacter();
        drawCharacter(rotAngle, jumpOffset, proneAngle, shiftAngle);
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glLoadIdentity();
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLdouble)w / (GLdouble)h, 1, 400);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case char (32):
            if(!gameStarted)
                startGame();
            break;
        case 'w':
            if(jumpOffset == 0.0)
            {
                jumping = true;
                if(proning)
                    proning = false;
            }
            break;
        case 's':
            if(proneAngle == 0.0)
                proning = true;
            else if(jumpOffset != 0)
                proning = true;
            break;
        case 'd':
            shiftAngle = 0.0;
            shifting = 1;
            position++;
            if(position>1)
                position = 1;
            break;
        case 'a':
            shiftAngle = 0.0;
            shifting = -1;
            position--;
            if(position < -1)
                position = -1;
            break;
        case 'q':
            std::cout<<"\n\nExiting Game...";
            std::cout<<"Thank You for playing!\n\n";
            exit(1);
        default:
            break;
    }
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000.0/60.0, timer, 0);
}

