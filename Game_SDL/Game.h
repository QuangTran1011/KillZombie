#pragma once
#ifndef GAME_H
#define GAME_H

#include "LTexture.h"
#include "NhanVat.h"
#include "Base.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Timer.h"
#include "TextObject.h"

void loadMedia();
int play(SDL_Renderer* gRenderer, SDL_Event& e);


#endif // !GAME_H

