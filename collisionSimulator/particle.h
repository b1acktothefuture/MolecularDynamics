#ifndef Particle_H_INCLUDED
#define Particle_H_INCLUDED

#include <math.h>
#include <stdlib.h>

const unsigned long int infinity = 2147483648;

struct ball {
    double radius;
    double rx;
    double ry;
    double vx;
    double vy;
    double mass;
};

struct color { double x, y, z; };

struct trail {
    double* x;
    double* y;
    int pos;
    int len = 500;
};

class Particle {
public:
    struct ball disc;
    struct color c;
    bool tr = 0;
    int count = 0;
    struct trail tail;
    Particle(double x1, double x2, double x3, double x4, double x5, double x6, bool t) {
        disc.radius = x1; disc.rx = x2; disc.ry = x3; disc.vx = x4; disc.vy = x5; disc.mass = x6;
        if (t == 1) trailEnable();
    };
    void trailEnable() {
        if(!tr){
        tr = 1;
        tail.x = (double*)malloc(tail.len * sizeof(double));
        tail.y = (double*)malloc(tail.len * sizeof(double));
        tail.pos = 0;
        for (int i = 0; i < tail.len; i++) {
            tail.x[i] = disc.rx;
            tail.y[i] = disc.ry;
        }
        return;
        }
        tr = 0;
    }
    void move(double dt);
    double timeToHit(Particle* that);
    double timeToHitVerticalWall();
    double timeToHitHorizontalWall();
    void bounceOffVerticalWall();
    void bounceOffHorizontalWall();
    void bounceOff(Particle* that);
};

#endif 