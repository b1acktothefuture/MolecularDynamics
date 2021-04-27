#include <Windows.h>
#include <GL\freeglut.h>
#include <iostream>
#include <stdio.h> 
#include "particle.h"
#include "collisionSystem.h"
#include "generateRandom.h"

using namespace std;

int pix1 = 600; // x axis
int pix2 = 600; // y axis
bool init = true;

collisionSystem col;

void drawShape(void) {
    Particle* temp;
    for (int i = 0; i < col.n; i++) {
        temp = col.particles[i];
        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i <= 50; i++) {
            double angle = 2 * 3.141 * i / 50;
            double x = temp->disc.rx + temp->disc.radius * cos(angle);
            double y = temp->disc.ry + temp->disc.radius * sin(angle);
            glVertex2d(pix1 * x, pix2 * y);
        }
        glEnd();
    }
}

void initRendering() {
    glEnable(GL_DEPTH_TEST);
}

// called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    glOrtho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawShape();
    glutSwapBuffers();
}

void update(int value) {
    col.simulate();
    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}


int main(int argc, char** argv) {
    int n = 100;
    Particle** arr;
    arr = (Particle**)(calloc(n, sizeof(Particle*)));
    for (int i = 0; i < n; i++) {
        arr[i] = new Particle(0.0,0.0,0.0,0.0,0.0,0.0);
    }
    generate(arr, n,0.2);
    col.construct(arr, n,&init,10000);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(pix1, pix2);
    glutCreateWindow("Moving particle");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    initRendering();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return(0);
}


