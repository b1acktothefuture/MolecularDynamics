#include "generateRandom.h"
int start;
double fact = 0.00000;
double two = 2.0000;

double randFloat(double a, double b)
{
	return ((b - a) * ((double)rand() / RAND_MAX)) + a;
}


void genBALL(Particle* p, double x1, double y1, double size) {
	p->disc.rx = randFloat(x1 + size*(0.5000- fact), x1 + size*(0.5000 + fact));
	p->disc.ry = randFloat(y1 + size * (0.5000 - fact), y1 + size * (0.5000 + fact));
	p->disc.vx = randFloat(0.0, 0.009*2.00) - 0.009;
	p->disc.vy = randFloat(0.0, 0.009*2.00) - 0.009;	
	double t = min(min(size + x1 - p->disc.rx, p->disc.rx - x1), min(size + y1 - p->disc.ry, p->disc.ry - y1));
	p->disc.radius = randFloat(t/two, t);
	p->disc.mass = (p->disc.radius)* (p->disc.radius);
	p->c.x = randFloat(0.3, 0.7);
	p->c.y = randFloat(0.3, 0.7);
	p->c.z = p->c.y;// randFloat(0.3, 0.7);
	/*
	For better distribution of radii, intitiaize the radius first and choose centre from a valid disc of radius =  size - rBALL;
	find a way to choose uniformly randomly from a disc or implement a 2D Gaussian distribution,
	current implementation has a bias towards small radii especially for large N due to independent uniform sampling for rx , ry and recursive implementation.
	*/
}

void randPos(int n,Particle** array, double x1, double y1, double size) {
	int k, r, t;
	if (n <= 4 ) {
		if (n != 0) {
			genBALL(array[start],x1, y1, size/two);
			start++;
			n--;
		}
		if (n != 0) {
			genBALL(array[start], x1 + size/two, y1, size / two);
			start++;
			n--;
		}
		if (n != 0) {
			genBALL(array[start], x1 + size / two, y1 + size / two, size / two);
			start++;
			n--;
		}
		if (n != 0) {
			genBALL(array[start], x1, y1 + size / two, size / two);
			start++;
			n--;
		}
		return;
	}
	if (n > 4) {
		k = n / 4;
		r = n % 4 + 1;
		t = rand() % r;
		randPos(k + t , array,  x1,  y1,  size/two);
		r = r - t;
		t = rand() % r;
		randPos(k + t , array, x1 + (size / two), y1, size / two);
		r = r - t;
		t = rand() % r;
		randPos(k + t, array, x1, y1 + (size / two), size / two);
		r = r - t;
		t = rand() % r;
		randPos(k + t, array, x1 + (size / two), y1 + (size / two), size / two);
	}
}

void lattice(Particle** arr, int N, double factor) {
	int n = ceil(sqrt(N)) + 1;
	double size = 1.00 / n;


}

void generate(Particle** arr, int N, double factor) {
	start = 0;
	fact = factor;
	srand((unsigned)time(0));
	randPos(N, arr, 0.00, 0.00, 1.0);
	start = 0;
}
