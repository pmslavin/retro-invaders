#include <cmath>
#include "shelter.h"

Shelter::Shelter(int ix, int iy, SDL_Surface *shelt) : x(ix), y(iy), sheltersurf(shelt){

	explosionSound = loadChunkResource(shelter_explosion01_ogg, shelter_explosion01_ogg_len);

}

void Shelter::paint(SDL_Surface *dest){

	std::vector<Explosion *>::iterator e;

	for(e = explosions.begin(); e != explosions.end(); e++){
		(*e)->paint(dest);
	}

	blitSurface(x, y, sheltersurf, dest);
}


void Shelter::clearExplosions(void){

	std::vector<Explosion *>::iterator e;

	for(e = explosions.begin(); e != explosions.end() ; ){
	
		delete *e;
		e = explosions.erase(e);
	
	}

}


SDL_Rect Shelter::rect(void){

	SDL_Rect rect = {x, y, sheltersurf->w, sheltersurf->h};

	return rect;
}


void Shelter::update(void){

	std::vector<Explosion *>::iterator e;

	for(e = explosions.begin(); e != explosions.end(); ){
		if( (*e)->age() > 48){
			delete *e;
			e = explosions.erase(e);
		}else{
			(*e)->update();
			e++;
		}
	}

}


void Shelter::locateImpact(Shot *a){

	int basex, basey, relx, rely, i;
	SDL_Rect shotRect = a->getRect();
	Uint32 zerocolour = SDL_MapRGB(sheltersurf->format, 0, 0, 0);
	Uint32 *point, *abovepoint;

	basex = shotRect.x + shotRect.w/2;

	if(a->getVel() > 0)
		basey = shotRect.y + shotRect.h;
	else{
//		a->setState(false);
//		return;
		basey = shotRect.y;
	}

	relx = basex - x;

	if(relx<0)
		relx = 0;

	if(relx>sheltersurf->w)
		relx = sheltersurf->w;

	rely = basey - y;

	if(rely < 0){
//		fprintf(stderr, "Cannon Shot out of shelter bound.\n");
		rely = 0;
	}

	if(rely > sheltersurf->h){
//		fprintf(stderr, "Alien Shot out of shelter bound.\n");
		rely = sheltersurf->h - 1;
	}

//	fprintf(stderr, "relx:rely %d:%d\n", relx, rely);



	if( SDL_MUSTLOCK(sheltersurf) ){
		if(SDL_LockSurface(sheltersurf))
			return;
	}

	point = (Uint32 *)sheltersurf->pixels + sheltersurf->pitch/4*rely + relx;

	if(*point == zerocolour){
		SDL_UnlockSurface(sheltersurf);
		return;
	}

	*point = zerocolour;

	if(a->getVel() > 0){
		for(i=1; i<=rely; i++){
			abovepoint = point - sheltersurf->pitch/4*i;
			if(*abovepoint == zerocolour)
				break;
			*abovepoint = zerocolour;
		}
/*		if(rely<(sheltersurf->h-1)){
			abovepoint = point + sheltersurf->pitch/4;
			*abovepoint = zerocolour;
		}
*/
	}else{
		for(i=1; i<(sheltersurf->h-rely-1); i++){
			abovepoint = point + sheltersurf->pitch/4*i;
			if(*abovepoint == zerocolour)
				break;
			*abovepoint = zerocolour;
		}

		if(rely < a->getRect().h*1.6){
		
			for(i=1; i<rely; i++){
				abovepoint = point - sheltersurf->pitch/4*i;
				*abovepoint = zerocolour;
			}
		}
	}
	SDL_UnlockSurface(sheltersurf);


/*		if(rely>y ){
				abovepoint = point - sheltersurf->pitch/4;
				*abovepoint = zerocolour;
			}
*/
	

/*	int cx=0, cy=0;
	Uint32 *cpoint;

	for(cy = 0; cy < sqrt(5*5 - cx*cx); cy++){
		for(cx = 0; cx < sqrt(5*5 - cy*cy); cx++){
			
			cpoint = point + cx;
			*cpoint = zerocolour;
			cpoint = point - cx;
			*cpoint = zerocolour;
		}
	}
*/

/*	if(relx != 0 && relx != sheltersurf->w){
		*(point-1) = zerocolour;
		*(point+1) = zerocolour;
	}
*/


	Mix_PlayChannel(-1, explosionSound, 0);
	explosions.push_back(new Explosion(x+relx, y+rely, 36, 2));
	a->setState(false);
}
