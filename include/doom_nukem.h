/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/05/20 17:37:20 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>

# include "sector.h"
# include "player.h"

# define MINWIDTH 800
# define MINHEIGHT 600
# define WIDTH 1280
# define HEIGHT 720
# define MAXWIDTH 1920
# define MAXHEIGHT 1080
# define PI 3.1415926535897932
# define PI180 0.01745329251
# define TOANGLE 57.2957795131
# define BLUE_SKY 0x4559a8ff
# define RED_WALL 0xb30000ff
# define PINK_FLOOR 0xdcc8c8ff
# define INT_MAX 2147483647
# define MAX_SPEED 50
# define RANGE 1 //range max for kick and actions with objects
# define TTFWOLF "ressources/font/wolfenstein.ttf"
# define TTFIMPACT "ressources/font/impact.ttf"

//le bunch permet de faire des groupe de mur visible
//pour organiser l'affichage
//over : indique si le mur depasse la vision mais et relier a un
//mur dans la vision
# define JOYSTICK_DEAD_ZONE 2500
# define SENSIBILITY 6.0

typedef struct s_doom	t_doom;
typedef	Uint32* t_texture;
# define JOYSTICK_DEAD_ZONE 2500

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
	struct s_sloc		*parent;
	int					snapy;
	t_vct2				pos;
}						t_sloc;

typedef struct			s_btn
{
	t_sloc				loc;
	SDL_Texture			*txture;
	SDL_Color			fgcolor;
	SDL_Color			bgcolor;
	char				*data;
	SDL_PixelFormat		*format;
	void				(*func)(t_doom *doom);
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
** 3 = Pause menu
*/

typedef struct			s_pal {
	Uint32				pal[38];
	int					height;
}						t_pal;

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
	t_pal				fire;
}						t_ui;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Window			*edwin;
	SDL_Renderer		*rend;
	t_vct2				size;
	t_vct2				m_pos;
	SDL_Texture			*txture;
	Uint32				*screen;
	t_tab				keys;
	SDL_PixelFormat		*format;
	Uint32				timp;
	int					fps;
}						t_sdl;

typedef struct s_pilier	*t_pilier;

struct					s_pilier {
	t_vct2				pos;

	t_pilier			prvs;
	t_pilier			next;
};

typedef struct			s_editor
{
	int					status;
	SDL_Window			*win;
	SDL_Renderer		*rend;
	t_btn				btnarr[20];
	t_vct2				size;
	SDL_Texture			*txture;
	Uint32				*screen;
	t_tab				keys;
	t_pilier			currpilier;
	t_pilier			map;
	t_vct2				mappos;
	int					mapzoom;
}						t_editor;

struct					s_doom
{
	t_sdl				sdl;
	t_editor			edit;
	t_ui				ui;
	Uint32				timestamp;
	t_player			player;
	SDL_GameController	*controller;
	t_sector			*sector;
	t_vct2				vel;
};

/*
** Button Functions
*/
void					start_button(t_doom *doom);
void					option_button(t_doom *doom);
void					return_button(t_doom *doom);

/*
** End Button Functions
*/
int						parsing(t_doom *doom, char *filename);

void					portal_engine(t_doom *doom);

void					fire_init(t_doom *doom);
void					fire(t_doom *doom);
void					fire_on_off(Uint32 *screen, t_vct2 size, int status);

void					sdl_showscreen(t_sdl *sdl);
void					btn_click(t_doom *doom, int x, int y);
t_btn					add_start_button(t_doom *doom);
t_btn					add_mapmenu_button(t_doom *doom);
t_btn					add_map_button(t_doom *doom, const char *str);
t_btn					add_doom_button(t_doom *doom);
t_btn					add_opt_button(t_doom *doom);
t_btn					add_editor_button(t_doom *doom);
t_btn					add_quit_button(t_doom *doom, const char *str,
																void *fc);
int						sdl_set_status(t_doom *doom, int status);
void					draw_menu(t_doom *doom);
int						load_map_btns(t_doom *doom);
void					update_loc(t_doom *doom, t_sloc *loc, t_sloc before);
void					update_slider_txt(t_doom *doom, t_slid *slid);
void					update_slider_value(t_doom *doom, t_slid *slid, int v);
t_slid					add_fov_slider(t_doom *doom);
void					draw_slid(t_doom *doom, t_slid *tmp);
int						event_handler(t_doom *doom);
int						event_handler1(t_doom *doom, SDL_Event event);
int						event_handler2(t_doom *doom, SDL_Event event);
int						loop_hook(t_doom *doom);
t_btn					*btn_hover(t_doom *doom, int x, int y);
void					draw_hover(t_doom *doom, t_btn *new, t_btn *old);

int						key_press(int key, t_doom *doom);
int						key_release(int key, t_doom *doom);
int						mouse_press(int button, int x, int y, t_doom *doom);
int						mouse_release(int button, int x, int y, t_doom *doom);
int						mouse_move(int x, int y, t_doom *doom);

double					double_modulo(double num);
double					angle_adaptater(double angle);
void					print_image(SDL_Surface *png);
unsigned int			color_rgb(uint8_t r, uint8_t g, uint8_t b);
void					*listdel(t_list **list);

char					**tab_new(int y);
void					controller_handler(t_doom *doom, SDL_Event event);
void					lst_del_node(t_list **node);
void					start_editor(t_doom *doom);
int						close_editor(t_doom *doom);
int						secure_doom(t_doom *doom);

/*
** Drawer functions
*/
void					sdl_cleartexture(Uint32 *screen, t_vct2 size);
void					big_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
int						fill_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
void					editor_fill_line(t_editor *ed, t_vct2 pos0, t_vct2 pos1, Uint32 color);
void					fill_line(t_sdl *sdl, t_vct2 pos0, t_vct2 pos1, Uint32 color);

/*
** Editor
*/
int						editor_key_press(int key, t_doom *doom);
int						editor_key_release(int key, t_doom *doom);
int						editor_mouse_press(int button, int x, int y,
																t_doom *doom);
int						editor_mouse_release(int button, int x, int y,
																t_doom *doom);
int						editor_mouse_move(SDL_MouseMotionEvent e, t_doom *doom);
void					draw_map(t_editor *editor);
t_pilier				ft_newpillar(t_vct2 loc);
t_pilier				ft_pillarpushend(t_pilier *start, t_vct2 loc);
void					ft_nodeprint_pillar(t_pilier node);
t_pilier				find_pilier(t_pilier start, int x, int y);

/*
**	gestion
*/
void					doom_exit(t_doom *doom);
t_doom					*doom_init();
void					editor_free(t_editor *editor);
int						editor_init(t_editor *editor);
void					sdl_free(t_sdl *sdl);
int						sdl_init(t_sdl *sdl, const char *title);
void					ui_free(t_ui *ui);
int						ui_init(t_ui *ui);
int						ui_by_sdl(t_doom *doom, t_ui *ui);

/*
**	simple input
*/
void					action(t_doom *doom);
void					PrintEvent(const SDL_Event *event);
void					debug_up(t_doom *doom);
void					sdl_present(t_sdl *sdl);
void					calcdelay(const char *str, t_doom *doom);

void					point_gras(t_vct2 cursor, Uint32 color, t_doom *doom);
void					trait(t_doom *doom, t_vct2 vct1, t_vct2 vct2, Uint32 col);
double					distance(t_fvct2 vct1, t_fvct2 vct2);

/*
**	parsing
*/
t_wall					*chunck_walls(t_list *chunck_line, size_t len);
t_player				chunck_player(int fd);
t_sector				*chunck_sector(int fd);
t_sector				*sector_new();
t_list					*ft_lstn(void *content);

/*
**	debug
*/
void					bold_point(t_vct2 cursor, Uint32 color, t_doom *doom);
void					draw_wall(t_doom doom, t_wall wall);
void					minimap(t_doom *d);
void					PrintEvent(const SDL_Event *event);
int						keyboard_input(t_doom *doom, SDL_Event event);
#endif
