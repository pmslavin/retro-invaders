#include "topbar.h"

TopBar::TopBar(TTF_Font *f, unsigned int v, Uint32 hs) : 
		score(0),
		hiscore(hs),
		font(f),
		level(1),
		sctext("1-UP"),
		hisctext("HI-SCORE"),
		levtext("LEVEL "),
		lives(v+1) {

	textcolour.r = 0xFF;
	textcolour.g = 0xFF;
	textcolour.b = 0xFF;
	textcolour.unused = 0;

	bar = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA | SDL_SRCCOLORKEY, SCREENW, 100, BPP,\
		       			screen->format->Rmask, screen->format->Gmask,\
					screen->format->Bmask, screen->format->Amask );

	SDL_SetColorKey(bar, SDL_SRCCOLORKEY, 0);

	scoretext = TTF_RenderText_Blended(font, sctext.c_str(), textcolour);
	hiscoretext = TTF_RenderText_Blended(font, hisctext.c_str(), textcolour);
	leveltext = TTF_RenderText_Blended(font, levtext.c_str(), textcolour);

}


void TopBar::paint(SDL_Surface *dest){

	std::ostringstream scss, hiscss, levss;
	scss << score;
	hiscss << hiscore;
	levss <<  level;
	std::string scntext = scss.str();
	std::string hiscntext = hiscss.str();
	std::string levntext = levss.str();
	
//	scoretext = TTF_RenderText_Blended(font, sctext.c_str(), textcolour);
	scorenum = TTF_RenderText_Blended(font, scntext.c_str(), textcolour);
//	hiscoretext = TTF_RenderText_Blended(font, hisctext.c_str(), textcolour);
	hiscorenum = TTF_RenderText_Blended(font, hiscntext.c_str(), textcolour);
//	leveltext = TTF_RenderText_Blended(font, levtext.c_str(), textcolour);
	levelnum = TTF_RenderText_Blended(font, levntext.c_str(), textcolour);

	SDL_FillRect(bar, &bar->clip_rect, SDL_MapRGB(bar->format, 0, 0, 0) );
	blitSurface(SCREENW/6, 20, scoretext, bar);
	blitSurface(SCREENW/6+(scoretext->w-scorenum->w)/2, 20+scoretext->h, scorenum, bar);
	blitSurface((SCREENW-hiscoretext->w)/2, 20, hiscoretext, bar);
	blitSurface((SCREENW-hiscorenum->w)/2, 20+hiscorenum->h, hiscorenum, bar);
	blitSurface(SCREENW-SCREENW/6, 20, leveltext, bar);
	blitSurface(SCREENW-SCREENW/6+(leveltext->w-levelnum->w)/2, 20+leveltext->h, levelnum, bar);

	if(lives){
		for(unsigned short int i=0; i<lives-1; i++){

			blitSurface(SCREENW-SCREENW/6+leveltext->w+16, 20+i*(cannonImage->h+5), cannonImage, bar);
		}
	}

	blitSurface(0, 0, bar, dest);

	SDL_FreeSurface(scorenum);
	SDL_FreeSurface(hiscorenum);
	SDL_FreeSurface(levelnum);
}


void TopBar::setScore(unsigned int s){

	score = s;

	if(score > hiscore){
		hiscore = s;
	}

}


void TopBar::addScore(unsigned int s){

	score += s;

	if(score > hiscore){
		hiscore += s;
	}
}
