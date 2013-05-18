#ifndef TITLE_H
#define TITLE_H

#include "sdlenv.h"
#include "starfield.h"
#include "hiscore.h"
#include "pointschart.h"
#include "credits.h"

class TitleScreen{

private:
	Starfield *starfield;
	Uint32 renderStart, panelCounter;
	const int FPS;
	TTF_Font *font96, *font48, *font18;
	SDL_Surface *titleText, *promptText;
	Mix_Music *music;
	HiScore *hstable;
	PointsChart *chart;
	Credits *credits;

public:
	TitleScreen(unsigned char font[], unsigned int fontlen, HiScore *hst);
	~TitleScreen(void);
	void paint(SDL_Surface *dest);
	void update(void);


};



#endif
