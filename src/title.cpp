#include "title.h"

TitleScreen::TitleScreen(unsigned char font[], unsigned int fontlen, HiScore *hst) : hstable(hst), renderStart(SDL_GetTicks()), panelCounter(0), FPS(100) {

	music = loadMusicResource(VMK_Galaxy_ogg, VMK_Galaxy_ogg_len);

	if(!music){
		fprintf(stderr, "Unable to load music file: %s\n", Mix_GetError());
	}

	Mix_PlayMusic(music, -1);	

/*	font96 = TTF_OpenFont(fontpath.c_str(), 96);
	font48 = TTF_OpenFont(fontpath.c_str(), 48);
	font18 = TTF_OpenFont(fontpath.c_str(), 18);
*/
	font18 = loadFontResource(font, fontlen, 18);
	font48 = loadFontResource(font, fontlen, 48);
	font96 = loadFontResource(font, fontlen, 96);


	chart = new PointsChart(font, fontlen);
	credits = new Credits(font18, font48);

	titleText = TTF_RenderText_Blended(font96, "RETRO INVADERS", white);
	promptText = TTF_RenderText_Blended(font18, "Press <SPACE> to start", green);
	starfield = new Starfield(400, 1000);

}


void TitleScreen::paint(SDL_Surface *dest){

	SDL_FillRect(dest, NULL, SDL_MapRGB(dest->format, 0, 0, 0) );
	starfield->DrawStars(dest);
	blitSurface((SCREENW-titleText->w)/2, SCREENH/8, titleText, dest);
	if(panelCounter == 1){
		SDL_Surface *hsTitle = TTF_RenderText_Blended(font48, "Hi-Scores", green);
		blitSurface((SCREENW-hsTitle->w)/2, SCREENH/8+2*titleText->h-hsTitle->h, hsTitle, dest);
		hstable->paintBody(dest, SCREENH/8+2.2*titleText->h);
		SDL_FreeSurface(hsTitle);
	}else if(panelCounter == 0){
		chart->paint(dest, SCREENH/8+1.5*titleText->h);
	}else if(panelCounter == 2){
		credits->paint(dest, SCREENH/8+2*titleText->h);
	}


	blitSurface((SCREENW-promptText->w)/2, SCREENH-SCREENH/7, promptText, dest);
	SDL_Flip(dest);

}


void TitleScreen::update(void){

	starfield->UpdateStars();
	if((SDL_GetTicks() - renderStart) > 4000){
		++panelCounter;
	       	panelCounter %= 3;
		renderStart = SDL_GetTicks();
	}

}


TitleScreen::~TitleScreen(void){

	Mix_HaltMusic();
	SDL_FreeSurface(titleText);
	SDL_FreeSurface(promptText);
	delete starfield;
	delete chart;
	delete credits;
//	TTF_CloseFont(font18);
//	TTF_CloseFont(font48);
//	TTF_CloseFont(font96);
	Mix_FreeMusic(music);
}
