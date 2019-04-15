#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <fcntl.h>
# include <SDL.h>
# include <SDL_ttf.h>

# define WIDTH 960
# define HEIGHT 540



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

/*
snap var behaviour
0 = center of object is its left;
1 = center of object is its center;
2 = center of object is its right;
*/
typedef struct		s_btn
{
	SDL_Rect		area;
	SDL_Texture		*txture;
	int				snapx; // See Snap var behaviour
	int				snapy; // See Snap var behaviour
	t_vct2			pos; // Will be percent of screen (0-100)
	SDL_Color		fgcolor;
	SDL_Color		bgcolor;
}					t_btn;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	TTF_Font		*font;
	SDL_Color		colorpal[10];
	t_btn			btnarr[50];
	t_vct2			size;
}					t_sdl;

typedef	struct		s_wolf
{
	t_sdl			sdl;
	char			map[100][100];
	t_vct2			map_size;
	t_fvct2			position;
}					t_wolf;


void			PrintEvent(const SDL_Event *event); // DEBUG

t_btn			add_start_button(t_wolf *wolf);
t_btn			add_wolf_button(t_wolf *wolf);

void			*sdldata_quit(t_sdl **data);
int				sdl_start(t_wolf *wolf, const char *title);
void			sdl_showscreen(t_sdl *sdl);
int				wolf_parseur(int ac, char **av, t_wolf *wolf);
int				raythrowing(t_wolf *wolf, int pixel_xi);

#endif
