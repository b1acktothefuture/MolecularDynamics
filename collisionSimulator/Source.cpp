#include <Windows.h>
#include <GL\freeglut.h>
#include <iostream>
#include "collisionSystem.h"
#include "generateRandom.h"

#define IX(n) double(n)/255.00

using namespace std;

int pix1 = 600; // x axis
int pix2 = 600; // y axis
bool init = true;
bool play = true;
collisionSystem* col;

void drawShape(void) {
    Particle* temp;
    int t = 90;
    for (int i = 0; i < col->n; i++) {
        temp = col->particles[i];
        glBegin(GL_POLYGON);
        glColor3f(temp->c.x , temp->c.y, temp->c.z);
        for (int i = 0; i <= t; i++) {
            double angle = 2.000 * 3.141857 * double(i) / double(t);
            double x = double(pix1) * (temp->disc.rx + temp->disc.radius * cos(angle));
            double y = double(pix2) * (temp->disc.ry + temp->disc.radius * sin(angle));
            glVertex2f( x, y);
        }
        glEnd();
    }
}

void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        play = !play;
}

Particle** initialize(int* n) {
    cout << "Enter no. of particles: ";
    cin >> *n;
    Particle** arr = (Particle**)(calloc(*n, sizeof(Particle*)));
    for (int i = 0; i < *n; i++) 
        arr[i] = new Particle(0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0); // initializing with zeros
    generate(arr, *n, 0.20); // assigning random positions and velocities
    return arr;
}

void initRendering() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glShadeModel(GL_SMOOTH);
    glutInitWindowSize(pix1, pix2);
    glutCreateWindow("Moving particle");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

}

// called when the window is resized
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, (double)w, 0.0f, (double)h, -1.0f, 1.0f);
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawShape();
    glutSwapBuffers();
}

void update(int value) {
    if (play)
        col->simulate();
    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}


int main(int argc, char** argv) {
    col = new collisionSystem;
    int n;
    Particle** arr = initialize(&n);
    col->construct(arr, n,&init,10000); // constructor for collision class
    glutInit(&argc, argv);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //reducing ALIASING, need to work on this// supersampling
    initRendering();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutMouseFunc(mouseFunc);
    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return(0);
}


