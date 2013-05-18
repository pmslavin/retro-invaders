#ifndef SHOT_H
#define SHOT_H

#include "sdlenv.h"


class Shot{

protected:
	int x, y, yvel;
	SDL_Surface *shotsurf;
	bool active;

public:
	explicit Shot(const int ix, const int iy, int vel, SDL_Surface *screen = screen);
	~Shot(void) { SDL_FreeSurface(shotsurf); }
	void paint(SDL_Surface *dest);
	void update(void);
	bool state (void) { return active; }
	void setState(bool state) { active = state; }
	SDL_Rect getRect(void); 
	int getVel(void) const { return yvel; }
};


#endif
