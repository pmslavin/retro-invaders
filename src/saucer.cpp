#include "saucer.h"


Saucer::Saucer(int iy, int p, SDL_Surface *surface, SDL_Surface *exp1, SDL_Surface *exp2)
		:  	y(iy),
			points(p),
			frame(0),
			killedframe(0),
			surf(surface),
			surfStore(surface),
			xstep(2),
			active(false)

{
	explosion[0] = exp1;
	explosion[1] = exp2;
	
	x = -surf->w;

//	explosionSound = Mix_LoadWAV("saucer-explosion.ogg");
	explosionSound = loadChunkResource(saucer_explosion_ogg, saucer_explosion_ogg_len);

	if(!explosionSound){
		fprintf(stderr, "Unable to load saucer explosion sound: %s\n", Mix_GetError() );
	}

//	whirr = Mix_LoadMUS("saucer-whirr.ogg");
	whirr = loadMusicResource(saucer_whirr_ogg, saucer_whirr_ogg_len);

	if(!whirr){
		fprintf(stderr, "Unable to load saucer whirr sound: %s\n", Mix_GetError() );
	}

}


SDL_Rect Saucer::rect(void){

	SDL_Rect rect = {x, y, surf->w, surf->h};
	return rect;
}


void Saucer::paint(SDL_Surface *dest){

	blitSurface(x, y, surf, dest);

}


void Saucer::update(void){

	if(x>SCREENW){ 
		resetState();
		return;
	}

	frame++;

	if(killedframe){

		if( (frame - killedframe) > 8){
			resetState();
			return;
		}

		if( (frame - killedframe) > 4){
			surf = explosion[1];
		}
	}

	x += xstep;
}


void Saucer::resetState(void){

	Mix_HaltMusic();
	Mix_RewindMusic();
	x = frame = killedframe = 0;
	active = false;
	surf = surfStore;
}



Saucer::~Saucer(void){

	SDL_FreeSurface(surf);
	SDL_FreeSurface(explosion[0]);
	SDL_FreeSurface(explosion[1]);
	Mix_FreeChunk(explosionSound);
	Mix_FreeMusic(whirr);
}



void Saucer::checkCollisions(Cannon *c){

	std::vector<CannonShot *>::iterator s;

	SDL_Rect shotRect;

	for(s=c->shots.begin(); s != c->shots.end(); s++){
	
		shotRect = (*s)->getRect();

		if( (shotRect.x + shotRect.w) > x && shotRect.x < (x + surf->w) ){
			if( shotRect.y < (y + surf->h) && (shotRect.y + shotRect.h) > y){
				(*s)->setState(false);
				c->addPoints(points);
				explode();
			}
		}
	}

}



void Saucer::explode(void){

	if(killedframe)
		return;

	Mix_HaltMusic();
	Mix_RewindMusic();
	Mix_PlayChannel(-1, explosionSound, 0);

	killedframe = frame;
	surf = explosion[0];

}


void Saucer::pauseSound(void){

	Mix_PauseMusic();
}

void Saucer::resumeSound(void){

	Mix_ResumeMusic();
}
