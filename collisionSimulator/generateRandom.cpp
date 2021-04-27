#include "generateRandom.h"
int start;
float fact = 0.0;

float randFloat(float a, float b)
{
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}


void genBALL(Particle* p, float x1, float y1, float size) {
	p->disc.rx = randFloat(x1 + size*(0.5000- fact), x1 + size*(0.5000 + fact));
	p->disc.ry = randFloat(y1 + size * (0.5000 - fact), y1 + size * (0.5000 + fact));
	p->disc.vx = randFloat(0.0, 0.008*2) - 0.008;
	p->disc.vy = randFloat(0.0, 0.008*2) - 0.008;
	
	float t = min(min(size + x1 - p->disc.rx, p->disc.rx - x1), min(size + y1 - p->disc.ry, p->disc.ry - y1));
	p->disc.radius = randFloat(t/float(2), t);
	p->disc.mass = (p->disc.radius)* (p->disc.radius);
}

void randPos(int n,Particle** array, float x1, float y1, float size) {
	int k, r, t;
	if (n <= 4 && n >0) {
		if (n != 0) {
			genBALL(array[start],x1, y1, size/float(2));
			start++;
			n--;
		}
		if (n != 0) {
			genBALL(array[start], x1 + size/float(2), y1, size / float(2));
			start++;
			n--;
		}
		if (n != 0) {
			genBALL(array[start], x1 + size / float(2), y1 + size / float(2), size / float(2));
			start++;
			n--;
		}
		if (n != 0) {
			genBALL(array[start], x1, y1 + size / float(2), size / float(2));
			start++;
			n--;
		}
		return;

	}
	if (n > 4) {
		k = n / 4;
		r = n % 4 + 1;
		t = rand() % r;
		randPos(k + t , array,  x1,  y1,  size/float(2));
		r = r - t;
		t = rand() % r;
		randPos(k + t , array, x1 + (size / float(2)), y1, size / float(2));
		r = r - t;
		t = rand() % r;
		randPos(k + t, array, x1, y1 + (size / float(2)), size / float(2));
		r = r - t;
		t = rand() % r;
		randPos(k + t, array, x1 + (size / float(2)), y1 + (size / float(2)), size / float(2));
	}
}

void generate(Particle** arr, int N, float factor) {
	start = 0;
	fact = factor;
	srand((unsigned)time(0));
	randPos(N, arr, 0, 0, 1.0);
	start = 0;
}
