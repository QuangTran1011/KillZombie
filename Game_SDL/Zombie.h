#pragma once
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "LTexture.h"
#include "Base.h"
#include "Bullet.h"

class Zombie : public LTexture {
public:

	Zombie();
	~Zombie();

	void render(SDL_Renderer* renderer, double x, double y, double z, double t);

	void SetClips();

	void move(double x, double y);

	bool checkHP();

	int GetPosX() { return zPosX; }
	int GetPosY() { return zPosY; }

	bool CheckVatcan();

protected:

	const int ZB_WIDTH = 47;
	const int ZB_HEIGHT = 74;

	int hp;

	double zPosX, zPosY;

	double  zVelY;

	int frame;

	const int ZB_VELX = 1;

	SDL_RendererFlip flipType;

	SDL_Rect ZBClips[8] = { 0 };
};

//_________________________________________________________
//_________________________________________________________

class Zombie1 : public LTexture {
public:

	Zombie1();
	~Zombie1();

	void render(SDL_Renderer* renderer, double x, double y, double z, double t);

	void SetClips();

	void move(double x, double y);

	bool checkHP();

	int GetPosX() { return zPosX; }
	int GetPosY() { return zPosY; }

	bool CheckVatcan();

protected:

	const int ZB1_WIDTH = 53;
	const int ZB1_HEIGHT = 75;

	int hp;

	double zPosX, zPosY;

	double  zVelY;

	int frame;

	const int ZB1_VELX = 2;

	SDL_RendererFlip flipType;

	SDL_Rect ZBClips[8] = { 0 };
};

//--------------------------------------------------------
class ZombieBoss : public LTexture {
public:

	ZombieBoss();
	~ZombieBoss();

	void render(SDL_Renderer* renderer, double x, double y, double z, double t);

	void SetClips();

	void move(double x, double y);

	bool checkHP();

	void SetPos(int x, int y) { zPosX = x;   zPosY = y; }

	void loadBullet(SDL_Renderer* renderer);

	void BulletMove(double x, double y);

	void set_bullet_list(std::vector<Bullet*> bullet_list_) {
		bullet_list = bullet_list_;
	}

	std::vector<Bullet*> get_bullet_list() const { return bullet_list; }

	void CreateBullet(SDL_Renderer* renderer, Mix_Chunk* b_sound);

	void makeBullet(SDL_Renderer* renderer, int& x, Mix_Chunk* b_sound);

	void RemoveBullet(const int& idx);

	void LoadimageHP(SDL_Renderer* renderer);

	void renderHP(SDL_Renderer* renderer);

	bool CheckVatcan();

protected:

	const int ZBBOSS_WIDTH = 200;
	const int ZBBOSS_HEIGHT = 193;

	int hp;

	double zPosX, zPosY;

	double  zVelY;

	int frame;

	const double ZBBoss_VELX = 1;

	SDL_RendererFlip flipType;

	SDL_Rect ZBBossClips[15] = { 0 };

	std::vector<Bullet*> bullet_list;

	LTexture HPTexture;
};

#endif // !ZOMBIE_H

