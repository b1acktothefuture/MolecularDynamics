#include "includes/collisionSystem.h"
#include <iostream>

void collisionSystem::construct(Particle **arr, int num, bool *indi, int lt, int md)
{
    particles = arr;
    n = num;
    limit = lt;
    mode = md;
    pq.push(new Event(0, NULL, NULL));
    for (int i = 0; i < n; i++)
    {
        predict(particles[i]);
    }
    pq.push(new Event(0, NULL, NULL));
    inti = indi;
}

void collisionSystem::redraw()
{
    if (t <= limit)
    {
        pq.push(new Event(t + 1 / HZ, NULL, NULL));
    }
}

void collisionSystem::predict(Particle *a)
{
    if (a == NULL)
        return;

    if (mode == 1)
    {
        a->c.x = ((a->disc.vx) * (a->disc.vx) + (a->disc.vy) * (a->disc.vy)) / (0.03 * 0.03);
        a->c.y = a->c.x;
        a->c.z = a->c.x;
    }

    // particle-particle collisions
    for (int i = 0; i < n; i++)
    {
        double dt = a->timeToHit(particles[i]);
        if (t + dt <= limit)
            pq.push(new Event(t + dt, a, particles[i]));
    }

    // particle-wall collisions
    double dtX = a->timeToHitVerticalWall();
    double dtY = a->timeToHitHorizontalWall();
    if (t + dtX <= limit)
        pq.push(new Event(t + dtX, a, NULL));
    if (t + dtY <= limit)
        pq.push(new Event(t + dtY, NULL, a));
}

void collisionSystem::simulate()
{

    while (!(pq.empty()) && (*inti))
    {

        // get impending event, discard if invalidated
        Event *e = pq.top();
        pq.pop();
        if (!e->isValid())
        {
            continue;
        }
        Particle *a = e->a;
        Particle *b = e->b;
        Particle *temp;
        // physical collision, so update positions, and then simulation clock
        for (int i = 0; i < n; i++)
            particles[i]->move(e->time - t);
        t = e->time;

        // process event
        if (a != NULL && b != NULL)
            a->bounceOff(b); // particle-particle collision
        else if (a != NULL && b == NULL)
            a->bounceOffVerticalWall(); // particle-wall collision
        else if (a == NULL && b != NULL)
            b->bounceOffHorizontalWall(); // particle-wall collision
        else if (a == NULL && b == NULL)
        {
            *inti = false;
            redraw();
        } // redraw event

        // update the priority queue with new collisions involving a or b
        predict(a);
        predict(b);
    }
    *inti = true;
}
