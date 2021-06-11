#ifndef Particle_H_INCLUDED
#define Particle_H_INCLUDED

#include <math.h>

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

class Particle {
public:
    struct ball disc;
    struct color c;
    bool trail = 0;
    int count = 0;
    double* start = NULL;
    double* stop = NULL;
    Particle(double x1, double x2, double x3, double x4, double x5, double x6, bool t) {
        disc.radius = x1; disc.rx = x2; disc.ry = x3; disc.vx = x4; disc.vy = x5; disc.mass = x6; trail = t;
        if (t) {
            start = new double[2];
            stop = new double[2];
        }
    };
    void move(double dt);
    double timeToHit(Particle* that);
    double timeToHitVerticalWall();
    double timeToHitHorizontalWall();
    void bounceOffVerticalWall();
    void bounceOffHorizontalWall();
    void bounceOff(Particle* that);
};

#endif 