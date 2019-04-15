#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "SDL2/SDL.h"

typedef struct		s_vct2
{
	int				x;
	int				y;
}					t_vct2;

typedef struct 		s_fvct2
{
	float			x;
	float			y;
}					t_fvct2;

typedef struct		s_sdldata
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Event		event;
	uint32_t		*screen;
	t_vct2			size;
	int				open;
}					t_sdldata;

typedef	struct		s_wolf
{
	t_sdldata		*data;
	char			map[100][100];
	t_vct2			map_size;
	t_fvct2			position;
}					t_wolf;

void			*sdldata_quit(t_sdldata **data);
t_sdldata		*sdldata_start(char *title, uint32_t x, uint32_t y);
void			sdl_showscreen(t_sdldata *sdl);
int				wolf_parseur(int ac, char **av, t_wolf *wolf);
int				raythrowing(t_wolf *wolf, int pixel_xi);
#endif
