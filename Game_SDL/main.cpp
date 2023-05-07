#include "Game.h"
#include "Menu.h"
#include <iostream>

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
		}
		gWindow = SDL_CreateWindow("Quang Tran ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					success = false;
				}
				if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
				{
					success = false;
				}
			}
		}
	}

	return success;
}


int main(int argc, char* args[])
{

	Menu menu;

	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		Mix_Music* music = NULL;
		music = Mix_LoadMUS("music/nhacnen.wav");
		std::string trangthai = "menu";
		SDL_Event e;

		while (trangthai != "exit") {
			if (trangthai == "menu") {
				if (Mix_PlayingMusic() == 0)
				{
					Mix_PlayMusic(music, -1);
				}
				if (Mix_PausedMusic) Mix_ResumeMusic();
				menu.renderMenuStart(gRenderer);
				int x = menu.checkstart(e);
				if (x == 1) {
					trangthai = "play";
				}

				else if (x == 2) {
					trangthai = "tutorial";
				}
				else if (x == 0) {
					SDL_Quit();
					return 0;
				}
				else continue;
			}

			if (trangthai == "play") {
				Mix_PauseMusic();
				int x = play(gRenderer, e);
				if (x == 1) {
					trangthai = "win";
				}
				else if (x == 0)
					trangthai = "lose";
				else {
					SDL_Quit();
					return 0;
				}
			}

			if (trangthai == "win") {
				menu.renderMenuWin(gRenderer);
				int x = menu.checkwin(e);
				if (x == 1) {
					trangthai = "menu";
				}
				else if (x == -1) {
					SDL_Quit();
					return 0;
				}
				else continue;

			}

			if (trangthai == "lose") {
				menu.renderMenuLose(gRenderer);
				int x = menu.checklose(e);
				if (x == 1) {
					trangthai = "menu";
				}
				else if (x == -1) {
					SDL_Quit();
					return 0;
				}
				else continue;
			}

			if (trangthai == "tutorial") {
				menu.renderTutorial(gRenderer);
				int x = menu.checkTutorial(e);
				if (x == 1) {
					trangthai = "menu";
				}
				else if (x == -1) {
					SDL_Quit();
					return 0;
				}
				else continue;
			}
		}
	}
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	return 0;
}