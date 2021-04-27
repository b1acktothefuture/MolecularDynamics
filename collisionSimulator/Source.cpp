#include <Windows.h>
#include <GL\freeglut.h>
#include <iostream>
#include "collisionSystem.h"
#include "generateRandom.h"

#define IX(n) float(n)/255.00

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
        glColor3f(IX(100) , IX(224), IX(181));
        for (int i = 0; i <= 1000; i++) {
            double angle = 2.000 * 3.141857 * float(i) / float(1000);
            double x = temp->disc.rx + temp->disc.radius * cos(angle);
            double y = temp->disc.ry + temp->disc.radius * sin(angle);
            glVertex2d(float(pix1) * x, float(pix2) * y);
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
    int n = 50;
    Particle** arr;
    arr = (Particle**)(calloc(n, sizeof(Particle*)));
    for (int i = 0; i < n; i++) {
        arr[i] = new Particle(0.0,0.0,0.0,0.0,0.0,0.0); // initializing with zeros
    }
    generate(arr, n,0.25); // assigning random positions and velocities
    col.construct(arr, n,&init,10000); // constructor for collision class
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(pix1, pix2);
    glutCreateWindow("Moving particle");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //reducing ALIASING, need to work on this// supersampling
    initRendering();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return(0);
}


