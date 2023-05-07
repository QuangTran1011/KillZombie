#ifndef NHAN_VAT_H
#define NHAN_VAT_H

#include <vector>
#include "LTexture.h"
#include "Bullet.h"


class NhanVat : public LTexture {
public:

	SDL_Rect camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };


	NhanVat();
	~NhanVat();

	double getPosX() { return mPosX; }
	double getPosY() { return mPosY; }

	void handleEvent(SDL_Event& e, SDL_Renderer* renderer, Mix_Chunk* bullet_sound);

	bool move();

	void render(SDL_Renderer* renderer);

	void SetClips();

	void SetCamera();

	bool checkHP(int x = 1);

	void set_bullet_list(std::vector<Bullet*> bullet_list_) {
		bullet_list = bullet_list_;
	}

	void HandleBullet(SDL_Renderer* renderer, double x);

	std::vector<Bullet*> get_bullet_list() const { return bullet_list; }

	void RemoveBullet(const int& idx);

	void LoadimageHP(SDL_Renderer* renderer);

	void renderHP(SDL_Renderer* renderer);

	bool CheckVatcan();
protected:
	SDL_Rect NhanVatClips[11] = { 0 };

	SDL_RendererFlip flipType;

	const int NV_WIDTH = 80;
	const int NV_HEIGHT = 69;
	const int NV_VEL = 3;

	std::vector<Bullet*> bullet_list;

	double mPosX, mPosY;

	double mVelX, mVelY;

	int frame;

	int hp;

	LTexture HPTexture;
};




#endif // !NHAN_VAT_H

