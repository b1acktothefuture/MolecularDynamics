#include "particle.h"

void Particle::move(double dt) {
    disc.rx += disc.vx * dt;
    disc.ry += disc.vy * dt;
}

double Particle::timeToHit(Particle* that) {
    if (disc.rx == that->disc.rx && disc.ry == that->disc.ry) {
        return infinity;
    }
    double dx = that->disc.rx - disc.rx;
    double dy = that->disc.ry - disc.ry;
    double dvx = that->disc.vx - disc.vx;
    double dvy = that->disc.vy - disc.vy;
    double dvdr = dvx * dx + dy * dvy;
    if (dvdr > 0) return infinity;
    double dvdv = dvx * dvx + dvy * dvy;
    if (dvdv == 0) return infinity;
    double drdr = dx * dx + dy * dy;
    double sigma = disc.radius + that->disc.radius;
    double d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
    if (d < 0) return infinity;
    return -(dvdr + sqrt(d)) / dvdv;

}

double Particle::timeToHitVerticalWall() {
    if (disc.vx > 0) return (1.0 - disc.rx - disc.radius) / disc.vx;  ///initialize pixel values
    else if (disc.vx < 0) return (disc.radius - disc.rx) / disc.vx;
    else             return infinity;
}

double Particle::timeToHitHorizontalWall() {
    if (disc.vy > 0) return (1.0 - disc.ry - disc.radius) / disc.vy;  ///initialize pixel values
    else if (disc.vy < 0) return (disc.radius - disc.ry) / disc.vy;
    else             return infinity;
}

void Particle::bounceOffVerticalWall() {
    disc.vx = -disc.vx;
    count++;
}

void Particle::bounceOffHorizontalWall() {
    disc.vy = -disc.vy;
    count++;
}

void Particle::bounceOff(Particle* that) {
    double dx = that->disc.rx - disc.rx;
    double dy = that->disc.ry - disc.ry;
    double dvx = that->disc.vx - disc.vx;
    double dvy = that->disc.vy - disc.vy;
    double dvdr = dx * dvx + dy * dvy;             // dv dot dr
    double dist = disc.radius + that->disc.radius;   // distance between particle centers at collison

    double magnitude = 2 * that->disc.mass * disc.mass * dvdr / ((disc.mass + that->disc.mass) * dist);
    double fx = magnitude * dx / dist;
    double fy = magnitude * dy / dist;

    // update velocities according to normal force
    disc.vx += fx / disc.mass;
    disc.vy += fy / disc.mass;
    that->disc.vx -= fx / that->disc.mass;
    that->disc.vy -= fy / that->disc.mass;

    count++;
    that->count++;
}
