#include "particle.h"

void Particle::paint(SDL_Surface *dest){

//	if(!active)
//		return;

	drawPixel(dest, x, y, colour.r, colour.g, colour.b);

	if(size){
		drawPixel(dest, x+1, y, colour.r, colour.g, colour.b);
		drawPixel(dest, x, y+1, colour.r, colour.g, colour.b);
		drawPixel(dest, x+1, y+1, colour.r, colour.g, colour.b);
	}

}


void Particle::update(void){

	x += xvel;
	y -= yvel;
	yvel -= gravity;
	age++;

	if( (x > SCREENW) || (y > SCREENH) || (age > 48 ))
		active = false;

	if(y>(SCREENH-16))
		y = SCREENH-16;

	xvel *= 0.9;	
	yvel *= 0.9;

	colour.r *= 0.97;
//	colour.g *= 0.97;
	colour.b *= 0.97;

}
