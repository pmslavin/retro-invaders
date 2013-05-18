#ifndef PHALANX_H
#define PHALANX_H

#include <vector>
#include "sdlenv.h"
#include "alien.h"
#include "cannon.h"
#include "shelter.h"


class Phalanx{

private:
	int rows, cols, xbase, ybase, descended;
	int xstep, ystep, lastx, lasty, moverate;
	int rowgap, colgap, level;
	std::vector<Alien *> aliens;
	std::vector<AlienShot *> alienshots;
	void descend(void);
	void shiftRow(int k);
	void resetPosition(Alien *a);

public:
	Phalanx(int c, int r);
	~Phalanx(void) {}
	void addAlien(Alien *a);
	void update(Uint32 elapsed);
	void updateShots(void);
	void paint(SDL_Surface *dest);
	void checkCollisions(Cannon *c);
	void clearShots(void);
	int count(void) const;
	void resetLevel(void);
	void shelterCollisions(Shelter *s, Cannon *c);

};


#endif
