#include "pointschart.h"

PointsChart::PointsChart(unsigned char font[], unsigned int fontlen){

/*	font18 = TTF_OpenFont(fontpath.c_str(), 18);
	font48 = TTF_OpenFont(fontpath.c_str(), 48);
*/
	font18 = loadFontResource(font, fontlen, 18);
	font48 = loadFontResource(font, fontlen, 48);

	topalien = loadImageResource(inv_topalien_01_png, inv_topalien_01_png_len);
	midalien = loadImageResource(inv_midalien_01_png, inv_midalien_01_png_len);
	botalien = loadImageResource(inv_botalien_01_png, inv_botalien_01_png_len);
	saucer = loadImageResource(inv_saucer_png, inv_saucer_png_len);

	titleText = TTF_RenderText_Blended(font48, "Score", green);
	equals = TTF_RenderText_Blended(font18, "=", white);
	tatext = TTF_RenderText_Blended(font18, "30 points", white);
	matext = TTF_RenderText_Blended(font18, "20 points", white);
	batext = TTF_RenderText_Blended(font18, "10 points", white);
	stext = TTF_RenderText_Blended(font18, "100 points", white);

	makeChart();

}

void PointsChart::paint(SDL_Surface *dest, int yOffset){

	blitSurface((SCREENW-chart->w)/2, yOffset, chart, dest);
}


void PointsChart::makeChart(void){

	int base(0), border(20);

	SDL_Surface *baseLine = TTF_RenderText_Blended(font18, "XXXXXXXXXXXXXXXXXXXX", white);

	chart = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, baseLine->w, 18*saucer->h,\
		       	BPP, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

	SDL_SetColorKey(chart, SDL_SRCCOLORKEY | SDL_RLEACCEL, 0);

	int picCol(chart->w/8), eqCol(chart->w/4+chart->w/9), pointsCol(chart->w/2+chart->w/16);

	blitSurface( (chart->w - titleText->w)/2, base, titleText, chart);

	base += titleText->h + border;

	blitSurface(picCol-topalien->w/2, base, topalien, chart);
	blitSurface(eqCol, base + (topalien->h - equals->h)/2, equals, chart);
	blitSurface(pointsCol, base + (topalien->h - tatext->h)/2, tatext, chart);

	base += topalien->h + border;

	blitSurface(picCol-midalien->w/2, base, midalien, chart);
	blitSurface(eqCol, base + (midalien->h - equals->h)/2, equals, chart);
	blitSurface(pointsCol, base + (midalien->h - matext->h)/2, matext, chart);

	base += midalien->h + border;

	blitSurface(picCol-botalien->w/2, base, botalien, chart);
	blitSurface(eqCol, base + (botalien->h - equals->h)/2, equals, chart);
	blitSurface(pointsCol, base + (botalien->h - batext->h)/2, batext, chart);

	base += 2*botalien->h + border;

	blitSurface(picCol-saucer->w/2, base, saucer, chart);
	blitSurface(eqCol, base + (saucer->h - equals->h)/2, equals, chart);
	blitSurface(pointsCol, base + (saucer->h - stext->h)/2, stext, chart);

	SDL_FreeSurface(baseLine);
}


PointsChart::~PointsChart(void){

	SDL_FreeSurface(chart);
	SDL_FreeSurface(topalien);
	SDL_FreeSurface(midalien);
	SDL_FreeSurface(botalien);
	SDL_FreeSurface(saucer);
	SDL_FreeSurface(titleText);
	SDL_FreeSurface(equals);
	SDL_FreeSurface(tatext);
	SDL_FreeSurface(matext);
	SDL_FreeSurface(batext);
	SDL_FreeSurface(stext);
//	TTF_CloseFont(font18);
//	TTF_CloseFont(font48);

}
