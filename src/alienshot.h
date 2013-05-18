#ifndef ALIENSHOT_H
#define ALIENSHOT_H

#include "sdlenv.h"
#include "shot.h"

class Alien;

class AlienShot : public Shot{

private:
	Alien *parent;

public:
	AlienShot(int ix, int iy, int vel, SDL_Surface *surf);
};


#endif
