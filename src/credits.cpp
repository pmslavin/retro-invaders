#include "credits.h"

Credits::Credits(TTF_Font *f18, TTF_Font *f48) : font18(f18), font48(f48){

	makePanel();

}


void Credits::makePanel(void){

	int base(0);

	creditsTitle = TTF_RenderText_Blended(font48, "Credits", green);
	codeText = TTF_RenderText_Blended(font18, "Coding and Design: Paul Slavin", white);
	musicText = TTF_RenderText_Blended(font18, "Title Music: VMK (8bc.org)", white);

	panel = SDL_CreateRGBSurface( SDL_HWSURFACE | SDL_SRCALPHA, codeText->w, 8*codeText->h, BPP, \
				screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

	SDL_SetColorKey(panel, SDL_SRCCOLORKEY | SDL_RLEACCEL, 0);	

	blitSurface((panel->w-creditsTitle->w)/2, base, creditsTitle, panel);

	base += creditsTitle->h + 20;

	blitSurface(0, base, codeText, panel);

	base += codeText->h + 20;

	blitSurface((panel->w - musicText->w)/2, base, musicText, panel);

}


void Credits::paint(SDL_Surface *dest, int yOffset){

	blitSurface( (dest->w - panel->w)/2, yOffset, panel, dest);

}


Credits::~Credits(void){

	SDL_FreeSurface(creditsTitle);
	SDL_FreeSurface(codeText);
	SDL_FreeSurface(musicText);
	SDL_FreeSurface(panel);
}
