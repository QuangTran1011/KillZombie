#include "Base.h"
#include "LTexture.h"
#include "TextObject.h"

#ifndef MENU_H
#define MENU_H

class Menu : public LTexture {
public:
	void renderMenuStart(SDL_Renderer* renderer);
	void renderMenuWin(SDL_Renderer* renderer);
	void renderMenuLose(SDL_Renderer* renderer);
	void renderTutorial(SDL_Renderer* renderer);

	int checkstart(SDL_Event& e);
	int checkwin(SDL_Event& e);
	int checklose(SDL_Event& e);
	int checkTutorial(SDL_Event& e);

protected:
	LTexture img_menustart;
	LTexture img_menuwin;
	LTexture img_menulose;
	LTexture img_tutorial;
};


#endif // !MENU_H

