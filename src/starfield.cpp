/*
 * Appropriate initial values:
 *
 * const int starcount = 400;
 * const int fielddepth = 1000;
 * const int FPS = 30;
 * int xCentre = 2, yCentre = 2;
 * const long double scalefactor = 0.1;
 *
 */

#include "starfield.h"


Starfield::Starfield(int count, int depth) : starcount(count), fielddepth(depth), FPS(30),
				 		xcentre(2), ycentre(2),
						scalefactor(0.1), renderStart(0) {


	stars = new Star[starcount];

	for(int i=0; i< starcount; ++i){
		stars[i].x = (rand() % SCREENW) - SCREENW/2;
		stars[i].y = (rand() % SCREENH) - SCREENH/2;
		stars[i].z = (rand() % fielddepth) + 1;
	}

}


Starfield::~Starfield(void){

	delete [] stars;
}



void Starfield::DrawStars(SDL_Surface *dest){

	SDL_LockSurface(dest);

	int xPos, yPos;
	Uint8 r,g,b;
	double gradient;
	for(int i=0; i< starcount; ++i){
		xPos = stars[i].x + SCREENW/xcentre;
		yPos = stars[i].y + SCREENH/ycentre;
		gradient = stars[i].z*1.5/(long double)fielddepth;
		gradient = (gradient < 1.0) ? gradient : 1.0;
		r = g = b = (Uint8)(32 + 223 * gradient);

		//fprintf(stderr,"stars[%d] z:%d r:g:b:%d\n",i,stars[i].z,r);
		if((rand() % 500) == 199){
			r = 0xFF;
			g = 0x00;
			b = 0x00;
		}
		if((rand() % 500) == 77){
			r = 0x00;
			g = 0x00;
			b = 0xFF;
		}

		//r = g = b = 0xFF;

		if((xPos > 0 && xPos < SCREENW) && (yPos > 0 && yPos < SCREENH) ){
//			fprintf(stderr, "Drawing: %d:%d:%d:%d\n", i, xPos, yPos, stars[i].z);
//			DrawPixel(screen, xPos, yPos, 0xFF, 0xFF, 0xFF);
			drawPixel(dest, xPos, yPos, r, g, b);
		}
	}

	SDL_UnlockSurface(dest);
}


void Starfield::UpdateStars(void){

	long double scale;
	int xPos, yPos;
	for(int i=0; i< starcount; ++i){
		scale = 1.0 + stars[i].z/(long double)fielddepth * scalefactor;
		stars[i].x *= scale;
		stars[i].y *= scale;
		stars[i].z += 10;
//		if( stars[i].z > fielddepth || stars[i].z < 0){
		xPos = stars[i].x + SCREENW/xcentre;
		yPos = stars[i].y + SCREENH/ycentre;
		if(xPos < 0 || xPos > SCREENW || yPos < 0 || yPos > SCREENH /*|| stars[i].z > fielddepth */){
			stars[i].x = (rand() % SCREENW) - SCREENW/xcentre;
			stars[i].y = (rand() % SCREENH) - SCREENH/ycentre;
			stars[i].z = rand() % (fielddepth/8);
		}
	}
}

/*
void Starfield::step(void)
{
	renderStart = SDL_GetTicks();

	DrawStars();
	UpdateStars();

	if((SDL_GetTicks() - renderStart) < (1000/FPS)){
		SDL_Delay(1000/FPS - (SDL_GetTicks() - renderStart) );
	}
}
*/
