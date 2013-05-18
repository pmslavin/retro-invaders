#include "phalanx.h"
#include <cmath>
#include <algorithm>


Phalanx::Phalanx(int c, int r) : cols(c), rows(r), level(1), descended(0) {

	lastx = xbase = SCREENW/10;
	lasty = ybase = 180;
	colgap = 0;
	rowgap = 10;
	xstep = 7;
	ystep = 18;
	moverate = 2;

}


void Phalanx::resetPosition(Alien *a){

	int x, y, w, h, r, c, colwidth, xpad, count;

	//std::vector<Alien *>::iterator p = std::find(aliens.begin(), aliens.end(), a);
	int p = std::find(aliens.begin(), aliens.end(), a) - aliens.begin();

//	if(p == aliens.size() )
//		count = aliens.size();
//	else
//		count = p - aliens.begin();

	count = p;
	
	r = count/cols;
	c = count % cols;

	w = a->getRect().w;
	h = a->getRect().h;
	//colwidth = (SCREENW-4*xbase)/cols - colgap;
	colwidth = 60;
	xbase = (SCREENW-cols*colwidth)/2;

	if(w < colwidth){
		xpad = (colwidth - w)/2;	
	}else{
		xpad = 0;
	}

//	fprintf(stderr, "colwidth:%d, awidth:%d\n", colwidth, w);

	x = xbase + xpad + c*(w+2*xpad+colgap);
	y = ybase + r*(h+rowgap);

	a->setPos(x, y);

}


void Phalanx::addAlien(Alien *a){

	resetPosition(a);
	aliens.push_back(a);
}


void Phalanx::paint(SDL_Surface *dest){

	std::vector<Alien *>::iterator a;

	for(a=aliens.begin(); a != aliens.end(); a++){
		if(!(*a)->getState())
			continue;

		(*a)->paint(dest);
	}	

	std::vector<AlienShot *>::iterator s;

	for(s=alienshots.begin(); s!=alienshots.end(); s++){
		if(!(*s)->state())
			continue;

		(*s)->paint(dest);
	}

}


void Phalanx::update(Uint32 elapsed){

	int r, c, x, y, i=0;
	//int colwidth = (SCREENW-2*xbase)/cols - colgap;
	int colwidth = 50;
	double shootprob = 3 + (7 * (aliens.size() - count())/aliens.size() );
//	fprintf(stderr, "shootprob:%f\n", shootprob);

	std::vector<Alien *>::iterator a;	
	for(a=aliens.begin(); a != aliens.end(); a++){
		if(!(*a)->getState()){
			i++;
			continue;
		}

		c = i % cols;
		r = i / cols;
		x = (*a)->getx();
		y = (*a)->gety();

		x += xstep;

		if( (x+(*a)->getRect().w) > SCREENW  || x < 0 ){
			x -= xstep;	
			x -= xstep;	
			xstep = -xstep;
			(*a)->setPos(x, y);
			shiftRow(i);
			if( (ybase + descended) < (SCREENH - SCREENH/3) ){
				descend();
			}
		}else{
			(*a)->setPos(x, y);
		}

		(*a)->flip();

		if( ((rand() % 100) > (100.0 - shootprob)) ){
			alienshots.push_back((*a)->shoot() );
		}
		
		i++;
	}
}


void Phalanx::updateShots(void){

	std::vector<AlienShot *>::iterator s;
	for(s=alienshots.begin(); s!=alienshots.end(); ){
		(*s)->update();
		if( !(*s)->state()){
			delete *s;
			alienshots.erase(s);
		}else{
			s++;
		}
	}

}


void Phalanx::descend(void){


	std::vector<Alien *>::iterator a;

	for(a=aliens.begin(); a != aliens.end(); a++){
		if(!(*a)->getState())
			continue;
		
		(*a)->setPos((*a)->getx(), (*a)->gety()+ystep);
	}

	descended += ystep;
}


void Phalanx::shiftRow(int k){

	Alien *a;

	for(int i=0; i<k; i++){
		a = aliens[i];
		if(!a->getState())
			continue;

		a->setPos(a->getx()+2*xstep, a->gety() );
	}
}


void Phalanx::checkCollisions(Cannon *c){

	std::vector<CannonShot *>::iterator s;
	std::vector<Alien *>::iterator a;
	std::vector<AlienShot *>::iterator b;

	SDL_Rect shotRect, alienRect;

	for(s = c->shots.begin(); s != c->shots.end(); s++){

		shotRect = (*s)->getRect();
		for(a = aliens.begin(); a != aliens.end(); a++){
			if(!(*a)->getState())
				continue;

			alienRect = (*a)->getRect();

//			fprintf(stderr,"sx:%d sy:%d sw:%d sh:%d ax:%d ay:%d aw:%d ah:%d\n", shotRect.x, shotRect.y,\
					shotRect.w, shotRect.h, alienRect.x, alienRect.y, alienRect.w, alienRect.h);

			if( (shotRect.x + shotRect.w) > alienRect.x && shotRect.x < (alienRect.x + alienRect.w) ){
				if( shotRect.y < (alienRect.y + alienRect.h) && (shotRect.y + shotRect.h) > alienRect.y){
					c->addPoints( (*a)->getPoints() );
					(*s)->setState(false);
//					(*a)->setState(false);
					(*a)->explode(screen);
					break;
				}
			}
		}
	}


	SDL_Rect cannonRect = {c->x, c->y, c->sf()->w, c->sf()->h};

	for(b = alienshots.begin(); b != alienshots.end(); b++){

		shotRect = (*b)->getRect();
		if( (shotRect.x + shotRect.w) > cannonRect.x && shotRect.x < (cannonRect.x + cannonRect.w) ){
			if( (shotRect.y + shotRect.h) > cannonRect.y && shotRect.y < (cannonRect.y + cannonRect.h) ){
				(*b)->setState(false);
				c->active = false;
				c->explode();
			}
		}
	}

}



void Phalanx::clearShots(void){

	std::vector<AlienShot *>::iterator s;

	for(s = alienshots.begin(); s != alienshots.end(); ){
		delete *s;
		s = alienshots.erase(s);	
	}

}


int Phalanx::count(void) const {

	int c=0;
	std::vector<Alien *>::const_iterator a;

	for(a = aliens.begin(); a != aliens.end(); a++){
	
		if((*a)->getState())
			c++;
	}

	return c;
}


void Phalanx::resetLevel(void){

	level++;

	if(level < 6){
		ybase += 2*ystep;
	}

	descended = 0;

	std::vector<Alien *>::iterator a;

	for(a = aliens.begin(); a != aliens.end(); a++){
		(*a)->resetState();
		resetPosition(*a);
	}
	
	clearShots();
}


void Phalanx::shelterCollisions(Shelter *s, Cannon *c){

	std::vector<AlienShot *>::iterator a;
	std::vector<CannonShot *>::iterator shot;
	SDL_Rect shotRect, shelterRect;

	shelterRect = s->rect();

	for(a = alienshots.begin(); a != alienshots.end(); a++){
		shotRect = (*a)->getRect();
	
		if( (shotRect.x + shotRect.w) > shelterRect.x && shotRect.x < (shelterRect.x + shelterRect.w) ){
			if( (shotRect.y + shotRect.h) > shelterRect.y && shotRect.y < (shelterRect.y + shelterRect.h) ){
				s->locateImpact(*a);
			}
		}
	}

	for(shot = c->shots.begin(); shot != c->shots.end(); shot++){
		shotRect = (*shot)->getRect();
	
		if( (shotRect.x + shotRect.w) > shelterRect.x && shotRect.x < (shelterRect.x + shelterRect.w) ){
			if( (shotRect.y + shotRect.h) > shelterRect.y && shotRect.y < (shelterRect.y + shelterRect.h) ){
				//(*shot)->setState(false);
				s->locateImpact(*shot);
			}
		}
	}

}
