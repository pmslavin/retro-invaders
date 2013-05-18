#ifndef BOTALIEN_H
#define BOTALIEN_H

#include "alien.h"


class BotAlien : public Alien{

private:
	int xvel, yvel, frameStep, killedFrame;
	SDL_Surface *explosion[2];

public:
	BotAlien(int ix, int iy, int p, SDL_Surface *frameOne, SDL_Surface *frameTwo, SDL_Surface *exp1, SDL_Surface *exp2);
	explicit BotAlien(int p, SDL_Surface *frameOne, SDL_Surface *frameTwo, SDL_Surface *exp1, SDL_Surface *exp2);
	~BotAlien(void) {}
	void paint(SDL_Surface *dest);
	void explode(SDL_Surface *exp);
	void update(void) {}
	AlienShot* shoot(void);
	void setPos(int nx, int ny) { x=nx; y=ny; }
	void flip(void) { frameStep++; }
	SDL_Surface *makeShotSurface(void);
	void resetState(void);

};


#endif
