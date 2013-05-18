#ifndef CANNONSHOT_H
#define CANNONSHOT_H

#include "sdlenv.h"
#include "shot.h"


class CannonShot : public Shot{

private:

public:
	explicit CannonShot(const int ix, const int iy, int vel, SDL_Surface *dest);
};


#endif
