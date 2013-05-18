#ifndef CANNON_H
#define CANNON_H

#include <vector>
#include "SDL/SDL.h"
#include "sdlenv.h"
#include "cannonshot.h"

class Cannon{

private:
	SDL_Surface *cannonsurf, *explosion, *cannonback;
	int x, y, xvel, yvel, score;
	std::vector<CannonShot *> shots;
	Mix_Chunk *shotSound, *explosionSound;
	bool active, shotactive;

public:
	Cannon(SDL_Surface *csurf, SDL_Surface *exp);
	~Cannon(void) { SDL_FreeSurface(cannonsurf); }
	void inputHandler(const SDL_Event &event);
	void update(void);
	void paint(SDL_Surface *dest);
	SDL_Surface *sf(void) const { return cannonsurf; }
	void setPos(int xpos, int ypos) { x=xpos; y=ypos; }
	void shoot(void);
	void addPoints(int points) { score += points; }
	int getScore(void) const { return score; }
	bool getState(void) const { return active; }
	void tempImmortal(void) { active = true; }
	void explode(void);
	void clearShots(void);
	void resetState(void);
	friend class Phalanx;
	friend class Saucer;

};



#endif
