#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <vector>
#include "particle.h"


class Explosion{

private:
	std::vector<Particle *> particles;
	int xcentre, ycentre, g, steps;


public:
	Explosion(int x, int y, int count, int grav);
	~Explosion(void) { deleteParticles(); }
	void paint(SDL_Surface *dest);
	void update(void);
	void deleteParticles(void);
	int age(void) const { return steps; }

};


#endif
