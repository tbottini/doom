/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/04/27 12:58:22 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <fcntl.h>
# include <dirent.h>

# define MINWIDTH 800
# define MINHEIGHT 600
# define WIDTH 1280
# define HEIGHT 720
# define PI 3.1415926535897932
# define PI180 0.01745329251
# define TOANGLE 57.2957795131
# define BLUE_SKY 0x4559a8ff
# define RED_WALL 0xb30000ff
# define PINK_FLOOR 0xdcc8c8ff
# define INT_MAX 2147483647
# define TTFWOLF "ressources/font/wolfenstein.ttf"
# define TTFIMPACT "ressources/font/impact.ttf"
# define WALLBLUE "ressources/textures/wall_blue.xpm"
# define WALL "ressources/textures/wall.xpm"
# define GOLD "ressources/textures/plaqueor.xpm"
# define TEST "ressources/textures/test.xpm"

# define JOYSTICK_DEAD_ZONE 2500

typedef struct			s_vct2
{
	int					x;
	int					y;
}						t_vct2;

typedef struct			s_fvct2
{
	double				x;
	double				y;
}						t_fvct2;

/*
** Snap var behaviour
** 0 = center of object is its left;
** 1 = center of object is its center;
** 2 = center of object is its right;
** 3 = under the object before + (pos) px
*/

typedef struct			s_sloc
{
	SDL_Rect			area;
	int					snapx;
	int					snapy;
	t_fvct2				pos;
}						t_sloc;

typedef struct			s_btn
{
	t_sloc				loc;
	SDL_Texture			*txture;
	SDL_Color			fgcolor;
	SDL_Color			bgcolor;
	char				*data;
	SDL_PixelFormat		*format;
}						t_btn;

typedef struct			s_slid
{
	t_sloc				loc;
	SDL_Texture			*txture;
	int					*val;
	int					min;
	int					max;
	SDL_Rect			grip;
	SDL_Color			fgcolor;
	SDL_Color			bgcolor;
}						t_slid;

typedef struct			s_font
{
	TTF_Font			*s32;
	TTF_Font			*s64;
	TTF_Font			*s128;
}						t_font;

/*
** m_status behaviour
** 0 = gamemode
** 1 = Show main menu
** 2 = show map menu
*/

typedef struct			s_ui
{
	t_font				fonts;
	t_btn				btnarr[20];
	t_btn				btnmap[20];
	t_btn				btnopt[20];
	t_slid				slidopt[10];
	t_slid				*currslid;
	int					m_status;
	t_btn				*curr_btn;
}						t_ui;

typedef struct			s_ray
{
	t_fvct2				inter_v;
	t_fvct2				inter_h;
	t_fvct2				ratio;
	float				angle;
	float				hor;
	float				ver;
	int					polar;
}						t_ray;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Window			*edwin;
	SDL_Renderer		*rend;
	t_vct2				size;
	t_vct2				m_pos;
	SDL_Texture			*txture;
	uint32_t			*screen;
	t_tab				keys;
	SDL_PixelFormat		*format;
}						t_sdl;

typedef struct			s_editor
{
	int					status;
	SDL_Window			*win;
	SDL_Renderer		*rend;
	t_vct2				size;
	SDL_Texture			*txture;
	t_tab				keys;
}						t_editor;

typedef struct			s_wall
{
	SDL_Surface			*surf;
	uint32_t			*txture;
	int					w;
	int					h;
}						t_wall;

typedef	struct			s_doom
{
	t_sdl				sdl;
	t_editor			edit;
	t_ui				ui;
	char				**map;
	t_vct2				map_size;
	t_fvct2				pos;
	double				rot;
	double				nrot;
	int					fov;
	t_wall				wall[4];
	unsigned long		timestamp;
	float				d_scrn;
	SDL_GameController	*controller;
	t_vct2				vel; // velocity
}						t_doom;

t_doom					*doom_init();
void					*sdldata_quit(t_sdl **data);
int						sdl_start(t_doom *doom, const char *title);
void					sdl_showscreen(t_sdl *sdl);
int						doom_parseur(t_doom *doom, char *filename);
int						prog_quit(t_doom *doom);
void					btn_click(t_doom *doom, int x, int y);
t_btn					add_start_button(t_doom *doom);
t_btn					add_mapmenu_button(t_doom *doom);
t_btn					add_map_button(t_doom *doom, const char *str);
t_btn					add_doom_button(t_doom *doom);
t_btn					add_opt_button(t_doom *doom);
t_btn					add_editor_button(t_doom *doom);
t_btn					add_quit_button(t_doom *doom, const char *str);
int						sdl_set_status(t_doom *doom, int status);
void					draw_menu(t_doom *doom);
int						load_map_btns(t_doom *doom);
void					update_loc(t_doom *doom, t_sloc *loc, t_sloc before);
void					update_slider_txt(t_doom *doom, t_slid *slid);
t_slid					add_fov_slider(t_doom *doom);
void					draw_slid(t_doom *doom, t_slid *tmp);
int						event_handler(t_doom *doom);
int						event_handler1(t_doom *doom, SDL_Event event);
int						event_handler2(t_doom *doom, SDL_Event event);
int						loop_hook(t_doom *doom);
t_btn					*btn_hover(t_doom *doom, int x, int y);
void					draw_hover(t_doom *doom, t_btn *new, t_btn *old);
void					move(t_doom *doom, int x, int y);
int						key_press(int key, t_doom *doom);
int						key_release(int key, t_doom *doom);
int						mouse_press(int button, int x, int y, t_doom *doom);
int						mouse_release(int button, int x, int y, t_doom *doom);
int						mouse_move(int x, int y, t_doom *doom);
void					raycasting(t_doom *doom);
float					float_modulo(float num);
double					angle_adaptater(double angle);
void					print_image(SDL_Surface *png);
float					ver_detection(t_doom *doom, t_ray *ray);
float					hor_detection(t_doom *doom, t_ray *ray);
double					iswall(t_doom *doom, t_fvct2 inter);
void					draw_column(t_doom *doom, t_ray ray, int num);
unsigned int			color_rgb(uint8_t r, uint8_t g, uint8_t b);
void					doom_clear_map(t_doom *doom);
int						map_check(t_doom *doom, char *filename);
int						row_verif(t_doom *doom, char *row);
void					*listdel(t_list **list);
t_vct2					*vct2_value(t_vct2 *vct2, int x, int y);
char					**tab_new(int y);
void					controller_handler(t_doom *doom, SDL_Event event);
void					lst_del_node(t_list **node);
int						start_editor(t_doom *doom);
int						close_editor(t_doom *doom);

void PrintEvent(const SDL_Event *event);

#endif
