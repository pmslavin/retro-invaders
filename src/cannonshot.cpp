#include "cannonshot.h"

CannonShot::CannonShot(const int ix, const int iy, int vel, SDL_Surface *dest) : Shot(ix, iy, vel, dest){

	shotsurf = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, 3, 7, 32, screen->format->Rmask,\
				screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

	SDL_SetColorKey(shotsurf, SDL_SRCCOLORKEY, 0);

	drawPixel(shotsurf, 2, 0, 0xFF, 0xFF, 0xFF);
	drawPixel(shotsurf, 1, 1, 0xFF, 0xFF, 0xFF);
	drawPixel(shotsurf, 0, 2, 0xFF, 0xFF, 0xFF);
	drawPixel(shotsurf, 1, 3, 0xFF, 0xFF, 0xFF);
	drawPixel(shotsurf, 2, 4, 0xFF, 0xFF, 0xFF);
	drawPixel(shotsurf, 1, 5, 0xFF, 0xFF, 0xFF);
	drawPixel(shotsurf, 0, 6, 0xFF, 0xFF, 0xFF);

}


