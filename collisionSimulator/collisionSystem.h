#pragma once
#include "particle.h"
#include <queue>
using namespace std;


class Event {
    int countA, countB;
public:
    Particle* a;
    Particle* b;
    double time;
    // Implement the compare method for this class 
    Event(double t, Particle* a1, Particle* b1) {
        time = t;
        a = a1;
        b = b1;
        if (a != NULL) countA = a->count;
        else countA = -1;
        if (b != NULL) countB = b->count;
        else countB = -1;
    }
    bool isValid() {
        if (a != NULL && (a->count != countA)) return false;
        if (b != NULL && (b->count != countB)) return false;
        return true;
    }

};


class eventCompare {
public:
    // Comparator function
    bool operator()(Event* A, Event* B) {
        // minimum ordering 
        if (A->time > B->time) {
            return true;
        }
        return false;
    }
};

class collisionSystem {

    double HZ = 0.8;
    priority_queue<Event*, vector<Event*>, eventCompare> pq;
    double t = 0.0;
    int limit;
    bool* inti;
public:
    int n;
    Particle** particles;
    void construct(Particle** arr, int num, bool* indi, int lt);
    void predict(Particle* a);
    void redraw();
    void simulate();
};

