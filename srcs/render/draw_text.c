#include "doom_nukem.h"

int sdl_string_put(SDL_Renderer *rend, TTF_Font *font, t_vct2 loc, const char *text, SDL_Color fg)
{
	SDL_Texture *texture;
	SDL_Surface *surf;
	SDL_Rect pos;

	surf = TTF_RenderText_Solid(font, text, fg);
	SDL_GetClipRect(surf, &pos);
	pos.x = loc.x;
	pos.y = loc.y;
	texture = SDL_CreateTextureFromSurface(rend, surf);
	SDL_RenderCopy(rend, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
	return (0);
}

int sdl_int_put(SDL_Renderer *rend, TTF_Font *font, t_vct2 loc, const char *label, const int value, SDL_Color fg)
{
	char *str;
	char *val;

	val = ft_itoa(value);
	str = ft_strjoin(label, val);
	sdl_string_put(rend, font, loc, str, fg);
	free(val);
	free(str);
	return (0);
}
