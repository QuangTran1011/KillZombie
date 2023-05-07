#ifndef BASE_H
#define BASE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <SDL_mixer.h>


static const int LEVEL_WIDTH = 6924;
static const int LEVEL_HEIGHT = 635;

static const int SCREEN_WIDTH = 1200;
static const int SCREEN_HEIGHT = 635;

static const int FRAME_PER_SECOND = 120;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

static Mix_Chunk* m_sound[4];
static Mix_Chunk* z_sound[1];
static Mix_Chunk* B_sound[2];


static SDL_Rect Vatcan[9] = { {710, 435, 150, 30}, { 1485, 550, 75, 50 }, { 2215, 492, 50, 36 },
							  { 2845, 410, 70, 50 }, { 3570, 590, 150, 620 }, { 5530, 400, 60, 45 },
							  { 3995, 440, 70, 40 }, { 4725, 520, 70, 50 }, { 6200, 565, 80, 55 } };

namespace SDLCommonFunc {
	bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
}

#endif 

