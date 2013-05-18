#include "cannon.h"
Cannon::Cannon(SDL_Surface *csurf, SDL_Surface *exp) : cannonsurf(csurf),
							explosion(exp),
							cannonback(csurf),
						x((SCREENW-cannonsurf->w)/2),
						y(SCREENH-2*cannonsurf->h),
						xvel(0),
						yvel(0),
       						score(0),
						active(true),
						shotactive(false)
{
//	shotSound = Mix_LoadWAV("cannon-shot.ogg");
	shotSound = loadChunkResource(cannon_shot_ogg, cannon_shot_ogg_len);
//	explosionSound = Mix_LoadWAV("cannon-explosion.ogg");
	explosionSound = loadChunkResource(cannon_explosion_ogg, cannon_explosion_ogg_len);
}


void Cannon::paint(SDL_Surface *dest){

	blitSurface(x, y, cannonsurf, dest);

	std::vector<CannonShot *>::iterator p;
	for(p=shots.begin(); p != shots.end(); p++){

		(*p)->paint(dest);	
	}
}


void Cannon::inputHandler(const SDL_Event &event){

	if(event.type == SDL_KEYDOWN){

		switch(event.key.keysym.sym){
		
			case SDLK_z:	if(xvel >= 0)	xvel -= 2;
					break;
			case SDLK_x:	if(xvel <= 0)	xvel += 2;
					break;
			case SDLK_PERIOD:	if(!shotactive){
							Mix_PlayChannel(1, shotSound, 0);
							shoot();
						}
						break;
			default:	break;
		
		}
	}else if(event.type == SDL_KEYUP){

		switch(event.key.keysym.sym){
			
			case SDLK_z:	if(xvel <= 0)	xvel += 2;
					break;
			case SDLK_x:	if(xvel >= 0)	xvel -= 2;
					break;
		
			default:	break;
		}
	}
}


void Cannon::update(void){

	x += xvel;

	if(x < 0 || x + cannonsurf->w > SCREENW)
		x -= xvel;

	std::vector<CannonShot *>::iterator p;
	for(p=shots.begin(); p != shots.end(); ){
		(*p)->update();	
		if(!(*p)->state()){
			delete *p;
			shots.erase(p);
			shotactive = false;
		}else{
			p++;		
		}
	}

}


void Cannon::shoot(void){

	//Mix_PlayChannel(-1, shotSound, 0);
	shotactive = true;
	int initx = x + cannonsurf->w/2 - 1;
	int inity = y + 2;
	shots.push_back(new CannonShot(initx, inity, -5, screen));

}


void Cannon::explode(void){

	Mix_PlayChannel(-1, explosionSound, 0);

	cannonback = cannonsurf;
	cannonsurf = explosion;

	active = false;
}


void Cannon::clearShots(void){

	std::vector<CannonShot *>::iterator s;

	for(s = shots.begin(); s != shots.end(); ){
	
		delete *s;
		s = shots.erase(s);
	}

}



void Cannon::resetState(void){

	Uint8 *keyState;
	active = true;
	shotactive = false;

	if(cannonsurf == explosion)
		cannonsurf = cannonback;

	SDL_PumpEvents();
	keyState = SDL_GetKeyState(NULL);

	if(!keyState[SDLK_z] && !keyState[SDLK_x] )
		xvel = yvel = 0;

	x = (SCREENW-cannonsurf->w)/2;
}
