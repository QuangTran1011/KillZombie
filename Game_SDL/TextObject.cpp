#include "TextObject.h"

TextObject::TextObject() {
	text_color.r = 255;
	text_color.b = 255;
	text_color.g = 255;
	texture = NULL;
}

TextObject::~TextObject() {

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* renderer) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		width = textSurface->w;
		height = textSurface->h;

		SDL_FreeSurface(textSurface);
	}

	//Return success
	return texture != NULL;
}

void TextObject::free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void TextObject::SetColor(int type) {
	if (type == RED_TEXT) {
		SDL_Color color = { 255,0,0 };
		text_color = color;
	}

	else if (type == RED_TEXT) {
		SDL_Color color = { 255,255,255 };
		text_color = color;
	}

	else if (type == RED_TEXT) {
		SDL_Color color = { 0,0,0 };
		text_color = color;
	}
}

void TextObject::RenderText(SDL_Renderer* renderer, int xp, int yp, SDL_Rect* clip,
	double angle, SDL_Point* center, SDL_RendererFlip flip) {

	SDL_Rect renderQuad = { xp,yp,width, height };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.w = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}