#include "midalien.h"

MidAlien::MidAlien(int ix, int iy, int p, SDL_Surface *frameOne, SDL_Surface *frameTwo, SDL_Surface *exp1, SDL_Surface *exp2) : Alien(ix, iy, p),
												frameStep(0),
												killedFrame(0),
												xvel(0),
												yvel(0) {

	frame[0] = storeFrame[0] = frameOne;
	frame[1] = storeFrame[1] = frameTwo;
	explosion[0] = exp1;
	explosion[1] = exp2;

}


MidAlien::MidAlien(int p, SDL_Surface *frameOne, SDL_Surface *frameTwo, SDL_Surface *exp1, SDL_Surface *exp2) :	Alien(p),
										frameStep(0),
										killedFrame(0),
										xvel(0),
										yvel(0) {

	frame[0] = storeFrame[0] = frameOne;
	frame[1] = storeFrame[1] = frameTwo;
	explosion[0] = exp1;
	explosion[1] = exp2;
}


void MidAlien::paint(SDL_Surface *dest){

	if(killedFrame && (frameStep - killedFrame) > 1){
		active = false;
		return;
	}	
	blitSurface(x, y, frame[frameStep%2], dest);

}


void MidAlien::explode(SDL_Surface *dest){

        if(killedFrame)
                return;

	Mix_PlayChannel(-1, explosionSound, 0);

        if(explosion[0] && explosion[1]){
                if(!(frameStep % 2)){
                        frame[0] = explosion[0];
                        frame[1] = explosion[1];
                }else{
                        frame[0] = explosion[1];
                        frame[1] = explosion[0];
                }
        }

        killedFrame = frameStep;
	points = 0;
}

SDL_Surface *MidAlien::makeShotSurface(void){

	SDL_Surface *shot = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA | SDL_SRCCOLORKEY, 3, 7, BPP, screen->format->Rmask, \
						screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

	SDL_SetColorKey(shot, SDL_SRCCOLORKEY, 0);

	drawPixel(shot, 0, 0, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 1, 1, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 2, 2, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 1, 2, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 0, 2, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 1, 3, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 2, 4, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 1, 4, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 0, 4, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 1, 5, 0xFF, 0x00, 0xFF);	
	drawPixel(shot, 2, 6, 0xFF, 0x00, 0xFF);	

	return shot;

}


AlienShot *MidAlien::shoot(void){

	Mix_PlayChannel(-1, shotSound, 0);

	int w = frame[0]->w;
	int h = frame[0]->h;
 
	AlienShot *shot = new AlienShot(x+w/2, y+h, 4, makeShotSurface() );

	return shot;

}


void MidAlien::resetState(void){

	active = true;
	points = storePoints;
	xvel = yvel = frameStep = killedFrame = 0;
	frame[0] = storeFrame[0];
	frame[1] = storeFrame[1];
}
