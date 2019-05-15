/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/05/05 20:44:04 by tbottini         ###   ########.fr       */
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
# define WALLBLUE "ressources/textures/wall_blue.xpm"
# define WALL "ressources/textures/wall.xpm"
# define GOLD "ressources/textures/plaqueor.xpm"
# define TEST "ressources/textures/test.xpm"

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

typedef struct s_pilier	t_pilier;
typedef t_pilier		*t_lstpil;

struct					s_pilier {
	t_vct2				pos;

	t_lstpil			prvs;
	t_lstpil			next;
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
	t_lstpil			currpilier;
	t_lstpil			map;
	t_vct2				mappos;
	int					mapzoom;
}						t_editor;

typedef	struct			s_weapon
{
	int					clip_max;
	int					ammo;
	int					clip;
	int					rate;
	int					dmg;
	void				*sprites;
}						t_weapon;

typedef struct 			s_player
{
	t_fvct2				pos;
	t_fvct2				rot;
	int					crouch;
	int					height;
	int					weight;
	int					speed;
	int					health;
	int					fov;
	t_fvct2				vel;
	t_fvct2				rotvel; // Rotvel needed for controller implementation
	int					hand;
	t_weapon			*weapons;
}						t_player;

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

float					ft_atof(char *str);
float					ft_catof(char *str, char c);
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

void					move(t_doom *doom, double x, double y);

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
void					open_editor(t_doom *doom);
int						close_editor(t_doom *doom);
int						secure_doom(t_doom *doom);
void					debug_player(t_player player);

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

t_lstpil				ft_newpillar(t_vct2 loc);
t_lstpil				ft_pillarpushend(t_lstpil *start, t_vct2 loc);
void					ft_nodeprint_pillar(t_lstpil node);
t_lstpil				find_pilier(t_lstpil start, int x, int y);

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
int						player_init(t_player *player);
void					player_free(t_player *player);

/*
**	simple input
*/

void					PrintEvent(const SDL_Event *event);
void					debug_up(t_doom *doom);
void					sdl_present(t_sdl *sdl);
void					calcdelay(const char *str, t_doom *doom);

void					point_gras(t_vct2 cursor, Uint32 color, t_doom *doom);
void					trait(t_doom *doom, t_vct2 vct1, t_vct2 vct2, Uint32 col);
float					distance(t_fvct2 vct1, t_fvct2 vct2);

/*
**	parsing
*/
t_wall					*chunck_walls(t_list *chunck_line, size_t len);
t_player				chunck_player(int fd);
t_sector				*chunck_sector(int fd);
t_fvct2					*double_atof(char *line, t_fvct2 *vct);
t_sector				*sector_new();
t_list					*ft_lstn(void *content);

/*
**	debug
*/
void					fvct2_msg(char *msg, t_fvct2 vct);
void					describe_bunch(t_wall **bunch);
void					fvct2_print(t_fvct2 vct);
void					sector_describe(t_sector sector);
void					bold_point(t_vct2 cursor, Uint32 color, t_doom *doom);
float					dist(t_fvct2 vct1, t_fvct2 vct2);

/*
** Gameplay
*/

void					action(t_doom *doom);
void					shoot(t_doom *doom);
void					reload(t_weapon *weapon);
void					crouch_release(t_doom *doom);
void					crouch(t_doom *doom);
void					sprint_release(t_doom *doom);
void					sprint(t_doom *doom);
void					next_weapon(t_player *player);
void					prev_weapon(t_player *player);

void					draw_wall(t_doom doom, t_wall wall);
void					minimap(t_doom *d);
void					PrintEvent(const SDL_Event *event);

#endif
