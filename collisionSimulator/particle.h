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

class Particle {
public:
    struct ball disc;
    int count = 0;
    Particle(double x1, double x2, double x3, double x4, double x5, double x6) {
        disc.radius = x1; disc.rx = x2; disc.ry = x3; disc.vx = x4; disc.vy = x5; disc.mass = x6;
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