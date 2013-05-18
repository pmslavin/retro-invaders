#ifndef CREDITS_H
#define CREDITS_H

#include "sdlenv.h"


class Credits{

private:
	SDL_Surface *creditsTitle, *codeText, *musicText, *panel;
	TTF_Font *font18, *font48;

public:
	Credits(TTF_Font *f18, TTF_Font *f48);
	~Credits(void);
	void makePanel(void);
	void paint(SDL_Surface *dest, int yOffset);


};


#endif
