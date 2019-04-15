#include "SDL2/SDL.h"
#include "libft.h"
int main()
{

	//modification dynamique avec des texture
	SDL_Window *window = NULL;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event event;
	int	open = 1;

	int pitch;
	void *tmp;
	uint32_t *screen;
	int i = 0;
	SDL_PixelFormat *format;
	screen = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("test3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 800);

	//sdl lock texture
	SDL_LockTexture(texture, NULL, &tmp, &pitch);

	screen = tmp;
	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

	while (open)
	{
		SDL_WaitEvent(&event);
		//if (event.type == SDL_QUIT)
		//	open = 0;
		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				ft_putendl("window resized");
			else if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				ft_putendl("try to close windows");
				open = 0;
			}
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				ft_putendl("escape");
				open = 0;
			}
			else if (event.key.keysym.sym == SDLK_w)
			{
				while (i != 800 * 799)
				{
					screen[i] = 255 * 125;
					i++;
				}
				SDL_RenderCopy(renderer, texture, NULL, NULL);
				SDL_RenderPresent(renderer);
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT && event.button.clicks >= 2)
				ft_putendl("double clic gauche");
			if (event.button.button == SDL_BUTTON_RIGHT)
				ft_putendl("clic droit");
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			if (event.motion.xrel != 0)
				ft_putnbrcr(event.motion.xrel);
			else if (event.motion.yrel != 0)
				ft_putnbrcr(event.motion.yrel);
		}
	}
	//SDL_UnlockTexture(texture);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_FreeFormat(format);
	return (0);
}