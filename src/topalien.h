#ifndef TOPALIEN_H
#define TOPALIEN_H

#include "alien.h"


class TopAlien : public Alien{

private:
	int xvel, yvel, frameStep, killedFrame;
	SDL_Surface *explosion[2];

public:
	TopAlien(int ix, int iy, int p, SDL_Surface *frameOne, SDL_Surface *frameTwo, SDL_Surface *exp1, SDL_Surface *exp2);
	explicit TopAlien(int p, SDL_Surface *frameOne, SDL_Surface *frameTwo, SDL_Surface *exp1, SDL_Surface *exp2);
	~TopAlien(void) {}
	void paint(SDL_Surface *dest);
	void update(void) {}
	AlienShot* shoot(void);
	void setPos(int nx, int ny) {x=nx; y=ny; }
	void flip(void) { frameStep++; }
	void setState(bool state);
	SDL_Surface *makeShotSurface(void);
	void explode(SDL_Surface *dest);
	void resetState(void);

};


#endif
