#include "alien.h"

Mix_Chunk * Alien::explosionSound;
Mix_Chunk * Alien::shotSound;

bool Alien::initBool = Alien::audioSIB();


bool Alien::audioSIB(void){


	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1){
		fprintf(stderr, "Unable to initialise audio.\n");
	}

	explosionSound = loadChunkResource(alien_explosion_ogg, alien_explosion_ogg_len);

	if(!explosionSound){
		fprintf(stderr, "Unable to load alien explosion: %s.\n", Mix_GetError() );	
	}


	shotSound = loadChunkResource(alien_shot_ogg, alien_shot_ogg_len);

	if(!shotSound){
		fprintf(stderr, "Unable to load alien shot: %s.\n", Mix_GetError() );	
	}

}

Alien::Alien(int p) : x(0), y(0), points(p), storePoints(p), active(true), exploding(false){
/*
	explosionSound = Mix_LoadWAV("alien-explosion.wav");

	if(!explosionSound){
		fprintf(stderr, "Unable to load alien explosion: %s\n.", Mix_GetError() );	
	}


	shotSound = Mix_LoadWAV("alien-shot.ogg");

	if(!shotSound){
		fprintf(stderr, "Unable to load alien shot: %s\n.", Mix_GetError() );	
	}
*/
}

void Alien::explode(SDL_Surface *dest){

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

