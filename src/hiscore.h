#ifndef HISCORE_H
#define HISCORE_H

#include <string>
#include <list>
#include "sdlenv.h"


typedef struct{
	Uint32 scr;
	char initials[3];

}Score_t;

const int entries = 10;


class HiScore{

private:
	std::string path, hiscoreText;
	int count;
	Score_t scores[entries];
	TTF_Font *font18, *font48;
	SDL_Surface *surface, *backdrop;
	void getInitials(Score_t &newHS);
	void promptInitials(void);

public:
	HiScore(TTF_Font *f18, TTF_Font *f48, SDL_Surface *bd);
	~HiScore(void);
	void paint(SDL_Surface *dest);
	void write(void);
	void read(void);
	Uint32 topScore(void) const { return scores[0].scr; }
	void addNew(Uint32 s);
	void makeDefault(void);
	void paintBody(SDL_Surface *dest, int yOffset);


};


#endif
