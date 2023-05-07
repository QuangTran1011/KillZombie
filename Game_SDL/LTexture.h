#ifndef LTEXTURE_H
#define LTEXTURE_H
#include "Base.h"

class LTexture
{
public:
	LTexture();
	~LTexture();

	void SetSize(const int& w, const int& h) { rect.w = w; rect.h = h; }
	void SetRect(const int& x, const int& y) { rect.x = x; rect.y = y; }

	SDL_Rect GetRect() const { return rect; }

	SDL_Texture* GetTexture() const { return mTexture; }

	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	void free();

	void render(SDL_Renderer* renderer, SDL_Rect* clip = NULL);


protected:
	SDL_Texture* mTexture;
	SDL_Rect rect;

};


#endif 
