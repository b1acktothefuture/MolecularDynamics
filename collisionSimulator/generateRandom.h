#pragma once
#include "particle.h"
#include <iostream>
using namespace std;


float randFloat(float a, float b);
void genBALL(Particle* p, float x1, float y1, float size);
void randPos(int n, Particle** array, float x1, float y1, float size);
void generate(Particle** arr, int N, float factor);
