#include "cannon.h"
#include "topalien.h"
#include "midalien.h"
#include "botalien.h"
#include "phalanx.h"
#include "topbar.h"
#include "shelter.h"
#include "saucer.h"
#include "hiscore.h"
#include "title.h"


void paintShelters(SDL_Surface *dest);
void makeShelters(int count);
void freeShelters(void);
void resetShelters(void);
void introduceLevel(TTF_Font *font);
SDL_Surface *makeBackdrop(void);


const int FPS = 100;
SDL_Event event;
//SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};
SDL_Surface *backdrop;
std::vector<Shelter *> shelters;
unsigned int level, phalanxms = 300;


int main(int argc, char *argv[])
{
	atexit(tidy);
	initialise("Retro Invaders");
	srand(time(NULL));
	Uint32 renderstart = 0;
	
	backdrop = makeBackdrop();
//	TTF_Font *overlayFont18 = TTF_OpenFont("Prototype.ttf", 18);
//	TTF_Font *overlayFont48 = TTF_OpenFont("Prototype.ttf", 48);
	TTF_Font *overlayFont18 = loadFontResource(Prototype_ttf, Prototype_ttf_len, 18);
	TTF_Font *overlayFont48 = loadFontResource(Prototype_ttf, Prototype_ttf_len, 48);
	HiScore hstable(overlayFont18, overlayFont48, backdrop);
//	hstable.makeDefault();
//	hstable.read();
//	hstable.paint(screen);
//	SDL_Flip(screen);
//	SDL_Delay(3000);
//	hstable.addNew(11250, "PMS");
//	hstable.paint(screen);
//	SDL_Flip(screen);
//	SDL_Delay(3000);
restart:
	level = 1;
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0) );

	TitleScreen *title = new TitleScreen(Prototype_ttf, Prototype_ttf_len, &hstable);
	SDL_Delay(1000);

	bool showTitle = true;
	while(showTitle){
		renderstart = SDL_GetTicks();
	
		title->paint(screen);
		title->update();
		
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_KEYDOWN){
			       if(event.key.keysym.sym == SDLK_SPACE){
					showTitle = false;
					delete title;
					//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0) );
					blitSurface(0, 0, backdrop, screen);
					SDL_Flip(screen);
					break;
				}
				if(event.key.keysym.sym == SDLK_q)	exit(0);
			}
		}
	
		if((SDL_GetTicks() - renderstart) < (1000/30)){
			SDL_Delay(1000/30 - (SDL_GetTicks() - renderstart) );
		}

	}

	SDL_Surface *lostLifeText = TTF_RenderText_Blended(overlayFont48, "Cannon Destroyed", white);
	SDL_Surface *gameOverText = TTF_RenderText_Blended(overlayFont48, "GAME OVER", white);
	SDL_Surface *levelClearText = TTF_RenderText_Blended(overlayFont48, "Level Cleared", white);
	SDL_Surface *pressSpaceText = TTF_RenderText_Blended(overlayFont18, "Press <SPACE> to continue", white);
	
	TopBar bar(overlayFont18, 3, hstable.topScore() );
	Saucer saucer(bar.lowerBound()+20, 100, loadImageResource(inv_saucer_png, inv_saucer_png_len), loadImageResource(inv_saucer_exp_01_png, inv_saucer_exp_01_png_len), loadImageResource(inv_saucer_exp_02_png, inv_saucer_exp_02_png_len) );
	Cannon *cannon = new Cannon(loadImageResource(inv_cannon_png, inv_cannon_png_len), loadImageResource(inv_cannon_exp_01_png, inv_cannon_exp_01_png_len) );
	bar.setCannonImage(cannon->sf());
	makeShelters(4);

/*	TopAlien *ta = new TopAlien(100, 100, 30, loadImage("inv-topalien.01.png"), loadImage("inv-topalien.02.png") );
	MidAlien *ma1 = new MidAlien(100, 200, 20, loadImage("inv-midalien.01.png"), loadImage("inv-midalien.02.png") );
	MidAlien *ma2 = new MidAlien(100, 250, 20, loadImage("inv-midalien.01.png"), loadImage("inv-midalien.02.png") );
	BotAlien *ba1 = new BotAlien(100, 350, 10, loadImage("inv-botalien.01.png"), loadImage("inv-botalien.02.png") );
	BotAlien *ba2 = new BotAlien(100, 400, 10, loadImage("inv-botalien.01.png"), loadImage("inv-botalien.02.png") );
	ta->paint(screen);
	ma1->paint(screen);
	ba1->paint(screen);
	ma2->paint(screen);
	ba2->paint(screen);
*/

	Phalanx phalanx(10,5);
	TopAlien *ta;
	for(int i=0; i<10; i++){
		ta = new TopAlien(30, loadImageResource(inv_topalien_01_png, inv_topalien_01_png_len), loadImageResource(inv_topalien_02_png, inv_topalien_02_png_len), loadImageResource(inv_topalien_exp_01_png, inv_topalien_exp_01_png_len), loadImageResource(inv_topalien_exp_02_png, inv_topalien_exp_02_png_len) );
		phalanx.addAlien(ta);
	}

	MidAlien *ma;
	for(int i=0; i<20; i++){
		ma = new MidAlien(20, loadImageResource(inv_midalien_01_png, inv_midalien_01_png_len), loadImageResource(inv_midalien_02_png, inv_midalien_02_png_len), loadImageResource(inv_midalien_exp_01_png, inv_midalien_exp_01_png_len), loadImageResource(inv_midalien_exp_02_png, inv_midalien_exp_02_png_len) );
		phalanx.addAlien(ma);
	}

	BotAlien *ba;
	for(int i=0; i<20; i++){
		ba = new BotAlien(30, loadImageResource(inv_botalien_01_png, inv_botalien_01_png_len), loadImageResource(inv_botalien_02_png, inv_botalien_02_png_len), loadImageResource(inv_botalien_exp_01_png, inv_botalien_exp_01_png_len), loadImageResource(inv_botalien_exp_02_png, inv_botalien_exp_02_png_len) );
		phalanx.addAlien(ba);
	}

	bar.paint(screen);
	phalanx.paint(screen);
	cannon->paint(screen);
	paintShelters(screen);
	SDL_Flip(screen);
	introduceLevel(overlayFont48);
//	bar.paint(screen);
//	phalanx.paint(screen);
//	paintShelters(screen);
//	cannon->paint(screen);
//	SDL_Flip(screen);

	Uint32 elapsed=0, shelterElapsed[4] = {0, 0, 0, 0};
	bool active = true;
	while(active){
		renderstart = SDL_GetTicks();

		if(SDL_PollEvent(&event)){
			cannon->inputHandler(event);
			if(event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym == SDLK_q)	exit(0);
			}
		}

		cannon->update();
		phalanx.updateShots();
		phalanx.checkCollisions(cannon);
		if(saucer.state())
			saucer.checkCollisions(cannon);

		for(unsigned int i = 0; i < shelters.size(); i++){
			phalanx.shelterCollisions(shelters[i], cannon);
			if( (SDL_GetTicks() - shelterElapsed[i]) > 40){
				shelters[i]->update();
				shelterElapsed[i] = SDL_GetTicks();
//				fprintf(stderr, "Update: %d\n", shelterElapsed);
			}

		}

		if(!phalanx.count()){
		
			blitSurface((SCREENW-levelClearText->w)/2, (SCREENH-levelClearText->h)/2, levelClearText, screen);
			blitSurface((SCREENW-pressSpaceText->w)/2, (SCREENH+levelClearText->h)/2, pressSpaceText, screen);
			SDL_Flip(screen);

			while(SDL_WaitEvent(&event)){
				if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
					break;			
			}

			level++;
			phalanxms = (int)phalanxms*0.8;
			bar.setLevel(level);
			cannon->resetState();
			saucer.resetState();
			phalanx.resetLevel();
			cannon->clearShots();
		//	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0) );
			blitSurface(0, 0, backdrop, screen);
			bar.paint(screen);
			phalanx.paint(screen);
			cannon->paint(screen);
			resetShelters();
			paintShelters(screen);
			SDL_Flip(screen);
			introduceLevel(overlayFont48);
			continue;
		}

		if(!saucer.state() && ( (rand() % 1000) == 977) )
			saucer.activate();

//		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0) );
		blitSurface(0, 0, backdrop, screen);

		if(!cannon->getState()){

			bar.decLives();
			//fprintf(stderr, "    lives:%d\n", bar.getLives());
			bar.paint(screen);
			cannon->paint(screen);
			phalanx.paint(screen);
			if(saucer.state()){
				saucer.paint(screen);
				saucer.pauseSound();
			}

			paintShelters(screen);

			if(bar.getLives()){
				blitSurface((SCREENW-lostLifeText->w)/2, (SCREENH-lostLifeText->h)/2, lostLifeText, screen);
				blitSurface((SCREENW-pressSpaceText->w)/2, (SCREENH+lostLifeText->h)/2, pressSpaceText, screen);
			}else{
				blitSurface((SCREENW-gameOverText->w)/2, (SCREENH-gameOverText->h)/2, gameOverText, screen);
				SDL_Flip(screen);
				while(SDL_WaitEvent(&event)){
					if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
					break;			
				}

				active = false;
				resetShelters();
				hstable.addNew(cannon->getScore());
				hstable.write();
				//blitSurface(0, 0, backdrop, screen);
				hstable.paint(screen);
				SDL_Flip(screen);
				
				while(SDL_WaitEvent(&event)){
					if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
					break;			
				}
				continue;
			}
			SDL_Flip(screen);
			phalanx.clearShots();
			cannon->clearShots();
			//SDL_Delay(3000);
			//SDL_WaitEvent(NULL);

			while(SDL_WaitEvent(&event)){
				if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){
					cannon->resetState();
					saucer.resumeSound();
					break;
				}
			}

			continue;

		}
		bar.setScore(cannon->getScore());
		bar.paint(screen);
		if(saucer.state()){
			saucer.paint(screen);
			saucer.update();
		}
		cannon->paint(screen);
		phalanx.paint(screen);
		paintShelters(screen);
		SDL_Flip(screen);

		if( (SDL_GetTicks() - elapsed) > phalanxms){
			phalanx.update(SDL_GetTicks() - elapsed);
			elapsed = SDL_GetTicks();
		}

		if( (SDL_GetTicks() - renderstart) < 1000/FPS )
			SDL_Delay(1000/FPS - (SDL_GetTicks() - renderstart) );
		
	
	}

	delete cannon;
	goto restart;
	return 0;
}


void deleteLocals(void){

}


void makeShelters(int count){

	int columns, colwidth, x, y;

	SDL_Surface **sheltersurf = new SDL_Surface*[count];

	columns = 2*count+1;
	colwidth = SCREENW/columns;

	for(int i=0; i<count; i++){
	
		sheltersurf[i] = loadImageResource(inv_shelter_png, inv_shelter_png_len);
		x = (2*i+1)*colwidth+(colwidth-sheltersurf[i]->w)/2;
		y = SCREENH-3*sheltersurf[i]->h;
		
		shelters.push_back(new Shelter(x, y, sheltersurf[i]));

	}


}


void paintShelters(SDL_Surface *dest){

	std::vector<Shelter *>::iterator shel;

	for(shel = shelters.begin(); shel != shelters.end(); shel++){
	
		(*shel)->paint(dest);
	}
}


void freeShelters(void){

	std::vector<Shelter *>::iterator shel;

	for(shel = shelters.begin(); shel != shelters.end(); ){
	
		delete *shel;
		shel = shelters.erase(shel);
	}
}


void introduceLevel(TTF_Font *font){

	std::ostringstream levelss;
	levelss << "Level " << level;
	SDL_Surface *levelText = TTF_RenderText_Blended(font, levelss.str().c_str(), white);
	blitSurface((SCREENW-levelText->w)/2, (SCREENH-levelText->h)/2, levelText, screen);
	SDL_Flip(screen);
	SDL_FreeSurface(levelText);
	SDL_Delay(3000);
}


void resetShelters(void){

	for(unsigned int i=0; i < shelters.size(); i++){
	
		shelters[i]->clearExplosions();
	}

}


SDL_Surface *makeBackdrop(void){

	SDL_Surface *temp = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREENW, SCREENH, BPP, screen->format->Rmask,\
		       		screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

	int x, y, i, starchance;
	SDL_Color colour;
	Uint8 lumin;

	for(i=0; i<200; i++){
	
		x = rand() % SCREENW;
		y = rand() % SCREENH;

		lumin = 0x40 + (rand() % 0xC0);

		starchance = rand() % 512;
		if(starchance == 479){
		
			colour.r = lumin;
			colour.g = 0;
			colour.b = 0;

		}else if(starchance == 313){
		
			colour.r = 0;
			colour.g = 0;
			colour.b = lumin;
		
		}else{
		
			colour.r = lumin;
			colour.g = lumin;
			colour.b = lumin;
		
		}

		drawPixel(temp, x, y, colour.r, colour.g, colour.b);
	}

	return temp;

}
