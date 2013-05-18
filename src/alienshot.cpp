#include "alienshot.h"

AlienShot::AlienShot(int ix, int iy, int vel, SDL_Surface *surf) : Shot(ix, iy, vel) {

	shotsurf = surf;

}

