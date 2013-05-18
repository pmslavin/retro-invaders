#ifndef ALIEN_H
#define ALIEN_H

#include "sdlenv.h"
#include "alienshot.h"


class Alien{

protected:
	SDL_Surface *frame[2], *storeFrame[2], *explosion[2];
	int x, y, points, storePoints, frameStep, killedFrame;
	bool active, exploding;
	static Mix_Chunk *explosionSound, *shotSound;
	static bool initBool;
	static bool audioSIB(void);

public:
	Alien(void) : x(0), y(0), active(true), exploding(false) {}
	explicit Alien(int p);
	explicit Alien(int ix, int iy, int p) : x(ix), y(iy), points(p), storePoints(p), active(true), exploding(false) {}
	virtual ~Alien(void) {}
	virtual void paint(SDL_Surface *dest) = 0;
	virtual void explode(SDL_Surface *dest);
	virtual void update(void) = 0;
	virtual AlienShot* shoot(void) = 0;
	virtual void setPos(int nx, int ny) = 0;
	virtual void flip(void) = 0;
	SDL_Rect getRect(void) { SDL_Rect rect = {x, y, frame[0]->w, frame[0]->h}; return rect; }
	int getx(void) const { return x; }
	int gety(void) const { return y; }
	bool getState(void) const { return active; }
	void setState(bool state)  {  active = state; }
	int getPoints(void) const { return points; }
	bool isExploding(void) { return exploding; }
	virtual void resetState(void) = 0;


};


#endif
