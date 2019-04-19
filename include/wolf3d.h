/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/04/19 17:57:55 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <SDL.h>
# include <SDL_ttf.h>

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265359

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
Snap var behaviour
0 = center of object is its left;
1 = center of object is its center;
2 = center of object is its right;
3 = under the object before + (pos) px
*/

typedef struct		s_btn
{
	SDL_Rect		area;
	SDL_Texture		*txture;
	int				snapx; // See Snap var behaviour
	int				snapy; // See Snap var behaviour
	t_fvct2			pos; // Will be percent of screen (0-100)
	SDL_Color		fgcolor;
	SDL_Color		bgcolor;
	char			*data;
}					t_btn;

/*
m_status behaviour
0 = gamemode
1 = Show main menu
2 = show map menu
*/

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	TTF_Font		*font;
	TTF_Font		*font32;
	TTF_Font		*font128;
	SDL_Color		colorpal[10];
	t_btn			btnarr[10];
	t_btn			btnmap[15];
	t_vct2			size;
	SDL_Texture		*txture;
	uint32_t		*screen;
	int				open;
	int				m_status;
	t_tab			keys;
}					t_sdl;

typedef	struct		s_wolf
{
	t_sdl			sdl;
	char			map[100][100];
	t_vct2			map_size;
	t_fvct2			pos;
	float			rot;
	int				fov;
}					t_wolf;


t_wolf *wolf_init();

void			PrintEvent(const SDL_Event *event); // DEBUG

void			btn_click(t_wolf *wolf, int x, int y);
t_btn			add_start_button(t_wolf *wolf);
t_btn			add_mapmenu_button(t_wolf *wolf);
t_btn			add_map_button(t_wolf *wolf, const char *str);
t_btn			add_wolf_button(t_wolf *wolf);
t_btn			add_opt_button(t_wolf *wolf);
t_btn			add_quit_button(t_wolf *wolf, const char *str);

void draw_menu(t_wolf *wolf);

int load_map_btns(t_wolf *wolf);

int				key_press(int key, t_wolf *wolf);
int				key_release(int key, t_wolf *wolf);
int				mouse_press(int button, int x, int y, t_wolf *wolf);
int				mouse_release(int button, int x, int y, t_wolf *wolf);
int				mouse_move(int x, int y, t_wolf *wolf);

int loop_hook(t_wolf *wolf);

void			*sdldata_quit(t_sdl **data);
int				sdl_start(t_wolf *wolf, const char *title);
void			sdl_showscreen(t_sdl *sdl);
int				wolf_parseur(t_wolf *wolf, char *filename);
void			raycasting(t_wolf *wolf);
unsigned int	color_rgb(unsigned char r, unsigned char g, unsigned char b);

int				event_handler(t_wolf *wolf);

int				prog_quit(t_wolf *wolf);

#endif
