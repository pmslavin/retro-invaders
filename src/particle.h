#ifndef PARTICLE_H
#define PARTICLE_H

#include "sdlenv.h"


class Particle{

private:
	int gravity, age, size;
	double x, y, xvel, yvel;
	bool active;
	SDL_Color colour;

public:
	Particle(int ix, int iy, double xv, double yv, int g, int s=0) :	x(ix),
									y(iy),
									xvel(xv),
									yvel(yv),
									gravity(g),
									age(0),
									active(true),
									size(s)
	{
		colour.r = 0xFF;
		colour.g = 0xFF;
		colour.b = 0xFF;
	}
	~Particle(void) {}
	void paint(SDL_Surface *dest);
	void update(void);
};


#endif
