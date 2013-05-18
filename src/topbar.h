#ifndef TOPBAR_H
#define TOPBAR_H

#include <sstream>
#include "sdlenv.h"

class TopBar{

private:
	unsigned int score, lives, level;
	Uint32 hiscore;
        std::string sctext, hisctext, levtext;
	SDL_Surface *bar, *scoretext, *hiscoretext, *leveltext, *scorenum, *hiscorenum, *levelnum, *lifetext;
	SDL_Surface *cannonImage;
	TTF_Font *font;
	SDL_Color textcolour;

public:
	TopBar(TTF_Font *f, unsigned int v, Uint32 hs);
	~TopBar(void) {}
	void setScore(unsigned int s);
	void addScore(unsigned int s);
	void setLives(int v) { lives = v+1; }
	void decLives(void) { --lives; }
	unsigned int getLives(void) const { return lives; }
	void paint(SDL_Surface *dest);
	void setCannonImage(SDL_Surface *cannon) { cannonImage = cannon; }
	void setLevel(unsigned int lev) { level = lev; }
	int lowerBound(void) { return bar->h; }

};


#endif
