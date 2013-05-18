#ifndef STARFIELD_H
#define STARFIELD_H

#include "sdlenv.h"

typedef struct star_t{
	int x, y, z;
	SDL_Color colour;
}Star;


class Starfield{

private:

	int starcount, fielddepth, FPS, xcentre, ycentre;
	Uint32 renderStart;
	long double scalefactor;
	Star *stars;
	SDL_Event event;

public:
	Starfield(int count, int depth);
	~Starfield(void);
	void UpdateStars(void);
	void DrawStars(SDL_Surface *dest);


};


#endif
