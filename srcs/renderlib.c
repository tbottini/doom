#include "wolf3d.h"

int main()
{
	t_sdldata	*sdl;
	//int			a = 255;
	int			i;

	i = 0;
	SDL_Init(SDL_INIT_VIDEO);
	sdl = sdldata_start("hello", 1000, 1000);
	while (i != 800 * 799)
	{
		sdl->screen[i] = i * 255 * 255;

		i++;
	}
	sdl_showscreen(sdl);


	SDL_Delay(3000);

}