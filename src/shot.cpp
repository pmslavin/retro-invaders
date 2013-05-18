#include "shot.h"

Shot::Shot(const int ix, const int iy, int vel, SDL_Surface *screen) : x(ix), y(iy), yvel(vel), active(true){

}


void Shot::paint(SDL_Surface *dest){

	blitSurface(x, y, shotsurf, dest);
}


void Shot::update(void){

	y += yvel;

	if( (y < 0) || (y > SCREENH) )
		active = false;
}


SDL_Rect Shot::getRect(void){

	SDL_Rect rect = {x, y, shotsurf->w, shotsurf->h};
       	return rect; 
}
