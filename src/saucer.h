#ifndef SAUCER_H
#define SAUCER_H


#include <vector>
#include "sdlenv.h"
#include "cannon.h"


class Saucer{

private:
	SDL_Surface *surf, *surfStore, *explosion[2];
	int x, y, points, xstep, frame, killedframe;
	bool active;
	Mix_Chunk *explosionSound;
	Mix_Music *whirr;


public:
	Saucer(int iy, int p, SDL_Surface *surface, SDL_Surface *exp1, SDL_Surface *exp2);
	~Saucer(void);
	void setPos(int ix, int iy) { x = ix; y = iy; }
	void paint(SDL_Surface *dest);
	void update(void);
	bool state(void) const { return active; }
	void resetState(void);
	int getPoints(void) const { return points; }
	SDL_Rect rect(void);
	void activate(void) { active = true; Mix_PlayMusic(whirr, -1); }
	void checkCollisions(Cannon *c);
	void explode(void);
	void pauseSound(void);
	void resumeSound(void);


};



#endif
