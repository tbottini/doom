#include "doom_nukem.h"

static int upper_left(void *ptr)
{
	SDL_Rect part;
	t_sdl *sdl;

	sdl = ptr;
	part.x = 0;
	part.y = 0;
	part.w = sdl->size.x / 2;
	part.h = sdl->size.y / 2;
	SDL_RenderCopy(sdl->rend, sdl->txture, &part, &part);
	return (0);
}

static int upper_right(void *ptr)
{
	SDL_Rect part;
	t_sdl *sdl;

	sdl = ptr;
	part.x = sdl->size.x / 2;
	part.y = 0;
	part.w = part.x;
	part.h = sdl->size.y / 2;
	SDL_RenderCopy(sdl->rend, sdl->txture, &part, &part);
	return (0);
}

static int bottom_left(void *ptr)
{
	SDL_Rect part;
	t_sdl *sdl;

	sdl = ptr;
	part.x = 0;
	part.y = sdl->size.y / 2;
	part.w = sdl->size.x / 2;
	part.h = part.y;
	SDL_RenderCopy(sdl->rend, sdl->txture, &part, &part);
	return (0);
}

static int bottom_right(void *ptr)
{
	SDL_Rect part;
	t_sdl *sdl;

	sdl = ptr;
	part.x = sdl->size.x / 2;
	part.y = sdl->size.y / 2;
	part.w = part.x;
	part.h = part.y;
	SDL_RenderCopy(sdl->rend, sdl->txture, &part, &part);
	return (0);
}

void	sdl_MultiRenderCopy(t_sdl *sdl)
{
	SDL_Thread *rend_ths[4];

	rend_ths[0] = SDL_CreateThread(&upper_left, "Upper Left screen", sdl);
	rend_ths[1] = SDL_CreateThread(&upper_right, "Upper Right screen", sdl);
	rend_ths[2] = SDL_CreateThread(&bottom_left, "Bottom Left screen", sdl);
	rend_ths[3] = SDL_CreateThread(&bottom_right, "Bottom Right screen", sdl);
	SDL_WaitThread(rend_ths[0], NULL);
	SDL_WaitThread(rend_ths[1], NULL);
	SDL_WaitThread(rend_ths[2], NULL);
	SDL_WaitThread(rend_ths[3], NULL);
}


/*
** A utiliser entre deux fonctions pour calculer le temps de latence
** (better use in loop_hook and stuff)
** calcdelay("begin", doom);
** printf("Je suis une fonction lente\n");
** calcdelay("end", doom);
*/

void	sdl_cleartexture(Uint32 *screen, t_vct2 size)
{
	int x;

	x = -1;
	while (++x < size.x * size.y)
	{
		if (screen[x])
			screen[x] = 0;
	}
}

void calcdelay(const char *str, t_doom *doom)
{
	printf(" %s %u |", str, SDL_GetTicks() - doom->timestamp);
	doom->timestamp = SDL_GetTicks();
}

int	pos_in_rect(SDL_Rect rect, int x, int y)
{
	if (rect.x < x && x < rect.x + rect.w
		&& rect.y < y && y < rect.y + rect.h)
	{
		return (1);
	}
	return (0);
}

void updateText(SDL_Renderer *rend, TTF_Font *font, SDL_Texture **text, SDL_Rect *loc, const char *str, SDL_Color fg, SDL_Color bg)
{
	SDL_Surface		*tmp;

	SDL_DestroyTexture(*text);
	tmp = TTF_RenderText_Shaded(font, str, fg, bg);
	SDL_GetClipRect(tmp, loc);
	*text = SDL_CreateTextureFromSurface(rend, tmp);
	SDL_FreeSurface(tmp);
}
