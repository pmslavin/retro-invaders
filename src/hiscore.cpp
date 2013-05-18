#include "hiscore.h"
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <fstream>


HiScore::HiScore(TTF_Font *f18, TTF_Font *f48, SDL_Surface *bd) : 	 count(entries),
									 backdrop(bd),
									 hiscoreText("HI-SCORES"),
									 font18(f18),
									 font48(f48)
{
	
	
	surface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, SCREENW, SCREENH, BPP, screen->format->Rmask, \
					screen->format->Gmask, screen->format->Bmask, screen->format->Amask);


	uid_t uid = getuid();
	
	struct passwd *pws = getpwuid(uid);

	std::string home_dir = pws->pw_dir;
	std::string conf_dir(home_dir);
	conf_dir += "/.retroinvaders";

	path = std::string(conf_dir);
	path += "/hiscore.dat";

/*	fprintf(stderr, "home_dir: %s\n", home_dir.c_str());
	fprintf(stderr, "conf_dir: %s\n", conf_dir.c_str());
	fprintf(stderr, "path: %s\n", path.c_str());
*/
	struct stat *statbuf = new struct stat;
	
	if(stat(path.c_str(), statbuf) != 0){
		mkdir(conf_dir.c_str(), 0755);
		makeDefault();
	}else{
		read();
	}

	delete statbuf;
}


HiScore::~HiScore(void){

	SDL_FreeSurface(surface);

}


void HiScore::makeDefault(void){

	int i;

	for(i=0; i<entries; i++){
			
		scores[i].scr = (entries-i)*1000;
		strcpy(scores[i].initials, "EJB");
	}

	write();
}


void HiScore::write(void){

	std::ofstream hsfile(path.c_str(), std::ios::binary);

	for(int i=0; i<entries; i++){
	
		hsfile << scores[i].scr;
		hsfile << scores[i].initials << std::endl;
	}

	hsfile.close();

}


void HiScore::read(void){

	std::ifstream hsfile(path.c_str(), std::ios::binary);
	int i;

	for(i=0; i<entries; i++){
	
		hsfile >> scores[i].scr;
		hsfile >> scores[i].initials;
//		fprintf(stderr, "[%d] %d:%s\n", i+1, scores[i].scr, scores[i].initials);
	}

}



void HiScore::paint(SDL_Surface *dest){


	//SDL_FillRect(surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0, 0, 0));
	blitSurface(0, 0, backdrop, surface);

	SDL_Surface *hsText = TTF_RenderText_Blended(font48, hiscoreText.c_str(), green);
	SDL_Surface *spaceText = TTF_RenderText_Blended(font18, "Press <SPACE> to continue", green);

	blitSurface((SCREENW-hsText->w)/2, SCREENH/6, hsText, surface);
	paintBody(surface, SCREENH/6+2*hsText->h);
	blitSurface((SCREENW-spaceText->w)/2, SCREENH-SCREENH/6, spaceText, surface);

	
	blitSurface(0, 0, surface, dest);

	SDL_FreeSurface(hsText);
	SDL_FreeSurface(spaceText);

}



void HiScore::paintBody(SDL_Surface *dest, int yOffset){

	SDL_Surface *baseline;	
	SDL_Surface *entry[entries];
	std::string numberFormat("%d");
	std::string scoreFormat("%d");
	std::string initFormat("%s");
	char tableLine[28];
	int i;

	baseline = TTF_RenderText_Blended(font18, "XXXXXXXXXXXXXXXXX", white);

	for(i=0; i<entries; i++){
	
		snprintf(tableLine, 28, numberFormat.c_str(), i+1);
		entry[i] = TTF_RenderText_Blended(font18, tableLine, white);
		blitSurface( (SCREENW-baseline->w)/2, yOffset+i*entry[i]->h, entry[i], dest);
		SDL_FreeSurface(entry[i]);

		snprintf(tableLine, 28, scoreFormat.c_str(), scores[i].scr);
		entry[i] = TTF_RenderText_Blended(font18, tableLine, white);
		blitSurface( (SCREENW-baseline->w)/2+baseline->w/4, yOffset+i*entry[i]->h, entry[i], dest);
		SDL_FreeSurface(entry[i]);

		snprintf(tableLine, 28, initFormat.c_str(), scores[i].initials);
		entry[i] = TTF_RenderText_Blended(font18, tableLine, white);
		blitSurface( (SCREENW-baseline->w)/2+(baseline->w-baseline->w/5), yOffset+i*entry[i]->h, entry[i], dest);
		SDL_FreeSurface(entry[i]);
	}

	
	SDL_FreeSurface(baseline);

}



void HiScore::addNew(Uint32 s){

	int i, index = -1;

	for(i=0; i<entries; i++){
		if(s > scores[i].scr){
			index = i;
			break;
		}
	}

	if(index == -1)
		return;

	std::string inits("___");

	for(i=entries-2; i >= index; i--){
	
		scores[i+1].scr = scores[i].scr;
		strncpy(scores[i+1].initials, scores[i].initials, 3);
	}

	scores[index].scr = s;
	strncpy(scores[index].initials, inits.c_str(), 3);

	getInitials(scores[index]);

}


void HiScore::promptInitials(void){

	SDL_Surface *entry[entries];
	std::string lineFormat("%d        %4d      %s");
	char tableLine[28];
	int i;

	//SDL_FillRect(surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0, 0, 0));
	blitSurface (0, 0, backdrop, surface);
	SDL_Surface *hsText = TTF_RenderText_Blended(font48, hiscoreText.c_str(), green);
	SDL_Surface *enterText = TTF_RenderText_Blended(font18, "Press <ENTER> to continue", white);
	SDL_Surface *newhsText = TTF_RenderText_Blended(font18, "New Hi-Score. Please enter your initials.", green);
	blitSurface((SCREENW-hsText->w)/2, SCREENH/6, hsText, surface);
	blitSurface((SCREENW-newhsText->w)/2, SCREENH-SCREENH/6, newhsText, surface);
	blitSurface((SCREENW-enterText->w)/2, SCREENH-SCREENH/6+newhsText->h, enterText, surface);

/*	for(i=0; i<entries; i++){
	
		snprintf(tableLine, 28, lineFormat.c_str(), i+1, scores[i].scr, scores[i].initials);
		entry[i] = TTF_RenderText_Blended(font18, tableLine, white);
		blitSurface( (SCREENW-entry[i]->w)/2, SCREENH/6+2*hsText->h+i*entry[i]->h, entry[i], surface);
	}
*/

	paintBody(surface, SCREENH/6+2*hsText->h);
	blitSurface(0, 0, surface, screen);
	SDL_Flip(screen);

}


void HiScore::getInitials(Score_t &newHS){

	promptInitials();

	SDL_Event event;
	int len=0;

	while(SDL_WaitEvent(&event)){
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z){

				if(len == 3)
					continue;

				newHS.initials[len] = (char)event.key.keysym.sym-'a'+'A';
				len++;
				promptInitials();
			}

			if(event.key.keysym.sym == SDLK_BACKSPACE && len > 0){
			
				len--;
				newHS.initials[len] = (char)'_';
				promptInitials();
			}

			if(event.key.keysym.sym == SDLK_RETURN){
			
				return;
			}
		}
	}


}

