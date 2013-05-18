#include "explosion.h"
#include <cmath>


Explosion::Explosion(int x, int y, int count, int grav) : xcentre(x), ycentre(y), g(grav), steps(0){

	int size=0;
	double vel, velsqr, xvel, xsqr, yvel;
	srand(time(NULL));

	for(int i=0; i < count; i++){
	
		vel = drand48() * 40.0;
		xvel = drand48() * 18.0;
		xsqr = pow(xvel, 2);
		velsqr = pow(vel, 2);
		yvel = sqrt(fabs(velsqr - xsqr));

		if(rand()%2){
			xvel = -xvel;
		}

		if(vel < 18.0){
			size = 1;
		}else{
			size = 0;
		}

		//fprintf(stderr, "vel:xsqr %f:%f\txvel:yvel %f:%f size:%d \n", vel, xsqr, xvel, yvel, size);
		particles.push_back(new Particle(x, y, xvel, yvel, g, size) );
	}

}


void Explosion::paint(SDL_Surface *dest){

	std::vector<Particle *>::iterator p;

	for(p=particles.begin(); p!=particles.end(); p++){
		(*p)->paint(dest);
	}

}


void Explosion::update(void){

/*	if((SDL_GetTicks() - elapsed) < 50)
		return;

	elapsed = SDL_GetTicks();
*/
	std::vector<Particle *>::iterator p;

	for(p=particles.begin(); p!=particles.end(); p++){
		(*p)->update();
	}

	steps++;
}


void Explosion::deleteParticles(void){

	
	std::vector<Particle *>::iterator p;

	for(p=particles.begin(); p!=particles.end(); ){
		delete (*p);
		p = particles.erase(p);
	}
}
