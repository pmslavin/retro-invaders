#ifndef POINTSCHART_H
#define POINTSCHART_H


#include "sdlenv.h"


class PointsChart{

private:
	SDL_Surface *chart;
	SDL_Surface *topalien, *midalien, *botalien, *saucer;
	SDL_Surface *titleText, *tatext, *matext, *batext, *stext, *equals;
	TTF_Font *font18, *font48;

public:
	PointsChart(unsigned char font[], unsigned int fontlen);
	~PointsChart(void);
	void paint(SDL_Surface *dest, int yOffset);
	void makeChart(void);

};


#endif
