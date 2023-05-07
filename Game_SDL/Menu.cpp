#include "Menu.h"

void Menu::renderMenuStart(SDL_Renderer* renderer) {
	img_menustart.loadFromFile("image/menu.jpg", renderer);
	img_menustart.render(renderer);
	SDL_RenderPresent(renderer);
}

void Menu::renderMenuWin(SDL_Renderer* renderer) {
	img_menuwin.loadFromFile("image/youwin.png", renderer);
	img_menuwin.render(renderer);
	SDL_RenderPresent(renderer);
}

void Menu::renderMenuLose(SDL_Renderer* renderer) {
	img_menulose.loadFromFile("image/gameover.jpg", renderer);
	img_menulose.render(renderer);
	SDL_RenderPresent(renderer);
}

void Menu::renderTutorial(SDL_Renderer* renderer) {
	img_tutorial.loadFromFile("image/tutorial.png", renderer);
	img_tutorial.render(renderer);
	SDL_RenderPresent(renderer);
}

int Menu::checkstart(SDL_Event& e) {
	if (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
		{
			return 0;
		}
		else {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x >= 82 && x <= 211 && y >= 62 && y <= 112 && e.type == SDL_MOUSEBUTTONDOWN) return 1;
			if (x >= 84 && x <= 208 && y >= 141 && y <= 193 && e.type == SDL_MOUSEBUTTONDOWN) return 0;
			if (x >= 83 && x <= 208 && y >= 211 && y <= 251 && e.type == SDL_MOUSEBUTTONDOWN) return 2;
		}
	}
	return 3;
}


int Menu::checkwin(SDL_Event& e) {
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
		{
			return -1;
		}
		else {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x >= 387 && x <= 467 && y >= 422 && y <= 502 && e.type == SDL_MOUSEBUTTONDOWN) return 1;
		}
	}
	return 0;
}

int Menu::checklose(SDL_Event& e) {
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
		{
			return -1;
		}
		else {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x >= 553 && x <= 651 && y >= 350 && y <= 444 && e.type == SDL_MOUSEBUTTONDOWN) return 1;
		}
	}
	return 0;
}

int Menu::checkTutorial(SDL_Event& e) {
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
		{
			return -1;
		}
		else {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x >= 923 && x <= 1030 && y >= 537 && y <= 601 && e.type == SDL_MOUSEBUTTONDOWN) return 1;
		}
	}
	return 0;
}