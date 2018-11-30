#include "Drawable.h"

Drawable::Drawable()
{
	TTF_Init();
	first = true;
	timer = 0;
}

Drawable::~Drawable() {}

void Drawable::AddText(int x, int y, const char * message, int size, SDL_Renderer * r)
{

	font = TTF_OpenFont("Resources/DroidSans.ttf", size); //set font and size
	if (first)
	{
		textSurface = TTF_RenderText_Solid(font, message, { 120,0,255 });
		first = false;
	}
	else
	{
		textSurface = TTF_RenderText_Solid(font, message, { 255,255,255 }); //set message of text
	}
	text = SDL_CreateTextureFromSurface(r, textSurface);
	text_width = textSurface->w;
	text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	textRect = { x, y, text_width, text_height };
	texts.push_back(text); //adds text to vector
	textRects.push_back(textRect); //adds text rect to vector in same position as the text
	messages.push_back(message);

}

void Drawable::AddImage(int x, int y, const char * filepath, SDL_Renderer * r)
{
	t = IMG_LoadTexture(r, filepath); //load image from assets
	textureRect.x = x;
	textureRect.y = y;
	SDL_QueryTexture(t, NULL, NULL, &textureRect.w, &textureRect.h);
	rects.push_back(textureRect); //adds the image to the vector
	textures.push_back(t); //adds the rect to the vector in the same posiion as the image
}

void Drawable::Render(SDL_Renderer * r)
{

	for (int i = 0; i < textures.size(); i++) { //loop through images
		SDL_RenderCopy(r, textures.at(i), NULL, &rects.at(i));
	}
	for (int i = 0; i < texts.size(); i++) { //loop through text
		SDL_RenderCopy(r, texts.at(i), NULL, &textRects.at(i));
	}
}

void Drawable::SwitchUp(SDL_Renderer *r)
{
	if (selected == 0)
	{
		textSurface = TTF_RenderText_Solid(font, messages.at(selected), { 255,255,255 });
		texts.at(selected) = SDL_CreateTextureFromSurface(r, textSurface);
		textSurface = TTF_RenderText_Solid(font, messages.at(selected + (texts.size() - 1)), { 120,0,255 });
		texts.at(selected + (texts.size() - 1)) = SDL_CreateTextureFromSurface(r, textSurface);
		selected = texts.size() - 1;
	}
	else
	{
		textSurface = TTF_RenderText_Solid(font, messages.at(selected), { 255,255,255 });
		texts.at(selected) = SDL_CreateTextureFromSurface(r, textSurface);
		textSurface = TTF_RenderText_Solid(font, messages.at(selected - 1), { 120,0,255 });
		texts.at(selected - 1) = SDL_CreateTextureFromSurface(r, textSurface);
		selected = selected - 1;
	}
}

void Drawable::SwitchDown(SDL_Renderer *r)
{
	if (selected == texts.size() - 1)
	{
		textSurface = TTF_RenderText_Solid(font, messages.at(selected), { 255,255,255 });
		texts.at(selected) = SDL_CreateTextureFromSurface(r, textSurface);
		textSurface = TTF_RenderText_Solid(font, messages.at(0), { 120,0,255 });
		texts.at(0) = SDL_CreateTextureFromSurface(r, textSurface);
		selected = 0;
	}
	else
	{
		textSurface = TTF_RenderText_Solid(font, messages.at(selected), { 255,255,255 });
		texts.at(selected) = SDL_CreateTextureFromSurface(r, textSurface);
		textSurface = TTF_RenderText_Solid(font, messages.at(selected + 1), { 120,0,255 });
		texts.at(selected + 1) = SDL_CreateTextureFromSurface(r, textSurface);
		selected = selected + 1;
	}
}

int Drawable::getSelected()
{
	return selected;
}