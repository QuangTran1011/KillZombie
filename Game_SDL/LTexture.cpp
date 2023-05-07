#include "LTexture.h"


LTexture::LTexture()
{
	mTexture = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.h = 0;
	rect.w = 0;

}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 161, 47, 127));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			rect.w = loadedSurface->w;
			rect.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		rect.h = 0;
		rect.w = 0;
		rect.x = 0;
		rect.y = 0;
	}
}


void LTexture::render(SDL_Renderer* renderer, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { rect.x, rect.y, rect.w, rect.h };

	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}


