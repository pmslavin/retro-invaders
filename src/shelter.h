#ifndef SHELTER_H
#define SHELTER_H

#include "sdlenv.h"
#include "shot.h"
#include "explosion.h"
#include <vector>


class Shelter{

private:
	std::vector<Explosion *> explosions;
	SDL_Surface *sheltersurf;
	Mix_Chunk *explosionSound;
	int x, y;

public:
	Shelter(int ix, int iy, SDL_Surface *shelt);
	void paint(SDL_Surface *dest);
	void update(void);
	SDL_Rect rect(void);
	void locateImpact(Shot *a);
	void clearExplosions(void);

};


#endif
