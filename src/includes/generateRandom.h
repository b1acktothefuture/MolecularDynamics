#pragma once
#include "particle.h"
#include <iostream>
using namespace std;


double randFloat(double a, double b);
void genBALL(Particle* p, double x1, double y1, double size);
void randPos(int n, Particle** array, double x1, double y1, double size);
void generate(Particle** arr, int N, double factor);
