/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:39:33 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 17:32:30 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include <fcntl.h>
# include <dirent.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <SDL_mixer.h>
# include <limits.h>
# include "libft.h"
# include "input.h"

# define MAXTXTRNUMBER 500
# define MAXFILENAMELEN 20

# define MINENEMYPOS 1
# define MAXENEMYNUMBER 4
# define MAXENEMYPOS (MINENEMYPOS + MAXENEMYNUMBER)

# define MINPROPSPOS 20
# define MAXPROPSNUMBER 14
# define MAXPROPSPOS (MINPROPSPOS + MAXPROPSNUMBER)
# define PROPHEALTH "ressources/props/health.xpm"
# define PROPCASS "ressources/props/cassette.png"
# define PROPMUN "ressources/props/ammo.png"
# define PROPRPILL "ressources/props/pill.png"
# define PROPGPILL "ressources/props/greenpill.png"
# define PROPBPILL "ressources/props/bluepill.png"
# define PROPJETPACK "ressources/props/jetpack.png"
# define PROPGUN "ressources/props/gun.png"
# define PROPSHOTGUN "ressources/props/shotgun.png"
# define PROPRIFLE "ressources/props/rifle.png"
# define PROPKEY1 "ressources/props/key1.png"
# define PROPKEY2 "ressources/props/key2.png"
# define PROPKEY3 "ressources/props/key3.png"
# define PROPCORE "ressources/props/botinium.png"

# define MINWPROPSPOS (MAXPROPSPOS + 1)
# define MAXWPROPSNUMBER 6
# define MAXWPROPSPOS (MINWPROPSPOS + MAXWPROPSNUMBER)
# define PROPBTN "ressources/props/closed_button.png"
# define PROPBTNOPEN "ressources/props/opened_button.png"
# define PROPWINBTN "ressources/props/victory_button.png"
# define PROPIMPACT "ressources/props/impact.png"
# define PROPARROW "ressources/props/arrowblood.png"
# define PROPCROSS "ressources/props/crossblood.png"
# define PROPEXIT "ressources/props/exitblood.png"

# define EDITMINWIDTH 1024
# define EDITMINHEIGHT 800

/*
** For sprites
** # define ISWRITING(x) (x == ED_SAVING || x == ED_WRITING
**											|| x == ED_FORME || x == ED_OPEN)
*/

# define ISWRITING(x) (x == ED_SAVING || x == ED_WRITING || x == ED_OPEN)

# define SPRITEPATH "ressources/sprites/0000.png"

# define KICKSTART 0
# define KICKLEN 3

# define GUNSTART (KICKSTART + KICKLEN)
# define GUNSHOOTSTART (GUNSTART + 1)
# define GUNSHOOTLEN 7
# define GUNRELOADSTART (GUNSHOOTSTART + GUNSHOOTLEN)
# define GUNRELOADLEN 3

# define SHOTGUNSTART (GUNRELOADSTART + GUNRELOADLEN)
# define SHOTGUNSHOOTSTART (SHOTGUNSTART + 1)
# define SHOTGUNSHOOTLEN 4
# define SHOTGUNRELOADSTART (SHOTGUNSHOOTSTART + SHOTGUNSHOOTLEN)
# define SHOTGUNRELOADLEN 12

# define RIFLESTART (SHOTGUNRELOADSTART + SHOTGUNRELOADLEN)
# define RIFLESHOOTSTART (RIFLESTART + 1)
# define RIFLESHOOTLEN 4
# define RIFLERELOADSTART (RIFLESHOOTSTART + RIFLESHOOTLEN)
# define RIFLERELOADLEN 17

# define ENDSPRITES (RIFLERELOADSTART + RIFLERELOADLEN)

# define ENEMYPATH "ressources/sprites/enemies_sprites/0000.png"

# define ENEMY1START 0
# define ENEMY2START 6
# define ENEMY3START 12
# define ENEMY4START 18
# define ENEMYDEATHSTART 24
# define BOSSDEATHSTART 33
# define DEATHLEN 9
# define ENEMYTXTRTOTAL 42

typedef struct s_mur		t_mur;
typedef t_mur				*t_lstmur;

typedef struct s_pilier		t_pilier;
typedef t_pilier			*t_lstpil;

typedef struct s_entity		t_entity;
typedef t_entity			*t_lstent;

typedef struct s_secteur	t_secteur;
typedef t_secteur			*t_lstsec;

typedef struct s_doom		t_doom;

/*
** selecttxtr 1 fill obvious
** selecttxtr 2 remplir sol de secteur
** selecttxtr 3 remplir type de props
*/
typedef enum				e_selecttxtr
{
	NOSELECT,
	FILL_TXTR,
	FILL_SOL,
	FILL_PROP,
	FILL_WPROP
}							t_selecttxtr;

/*
** m_status behaviour
** 0 = gamemode
** 1 = Show main menu
** 2 = show map menu
** 3 = Option menu
** 4 = Pause menu in game
** 5 = Option menu in game
*/

typedef enum				e_menu_status {
	MENU_INGAME = 0,
	MENU_MAIN = 1,
	MENU_MAP = 2,
	MENU_OPTION = 3,
	MENU_IGMAIN = 4,
	MENU_IGOPTION = 5
}							t_menu_status;

typedef struct				s_font
{
	TTF_Font				*s32;
	TTF_Font				*s64;
	TTF_Font				*s128;
}							t_font;

typedef struct				s_pal {
	Uint32					pal[38];
	int						height;
	Uint32					*screen;
	t_vct2					*size;
}							t_pal;

/*
** editor coord on map
*/
typedef struct				s_ecoord
{
	t_secteur				*sector;
	t_mur					*mur;
	t_secteur				*mursec;
	t_vct2					pos;
	int						type;
	double					roty;
}							t_ecoord;

typedef struct				s_eplayer
{
	t_ecoord				stat;
}							t_eplayer;

struct						s_entity
{
	t_ecoord				stat;
	t_entity				*next;
	t_entity				*prev;
};

struct						s_pilier
{
	int						id;
	t_vct2					pos;
	t_lstpil				prvs;
	t_lstpil				next;
};

struct						s_mur
{
	t_pilier				*pil1;
	t_pilier				*pil2;
	SDL_Texture				*txtr;
	int						idtxtr;
	t_secteur				*portal_ptr;
	t_portal_id				portal_id;
	t_lstent				wproplist;
	t_lstmur				prvs;
	t_lstmur				next;
	int						id;
	int						level;
};

struct						s_secteur
{
	int						id;
	t_lstmur				murs;
	SDL_Texture				*top;
	int						idtop;
	SDL_Texture				*sol;
	int						idsol;
	int						hsol;
	int						htop;
	char					gravity;
	t_lstsec				prvs;
	t_lstsec				next;
};

/*
** Snap var behaviour
** 0 = center of object is its left;
** 1 = center of object is its center;
** 2 = center of object is its right;
** 3 = under the object before + (pos) px
** 4 = center of the object before + (pos) px
** 5 = over the object before + (pos) px
*/

typedef struct				s_sloc
{
	SDL_Rect				area;
	SDL_Rect				*parent;
	int						snapx;
	int						snapy;
	t_vct2					pos;
}							t_sloc;

typedef struct				s_html
{
	t_sloc					loc;
	SDL_Texture				*txtr;
}							t_html;

typedef struct				s_btn
{
	t_sloc					loc;
	SDL_Texture				*txture;
	SDL_Color				fgcolor;
	SDL_Color				bgcolor;
	char					*data;
	void					(*func)(t_doom *doom);
}							t_btn;

typedef struct				s_slid
{
	t_sloc					loc;
	SDL_Texture				*txture;
	SDL_Texture				*label;
	int						*val;
	int						min;
	int						max;
	SDL_Rect				grip;
	SDL_Rect				griplabel;
	SDL_Color				fgcolor;
	SDL_Color				bgcolor;
}							t_slid;

typedef struct				s_ui
{
	t_font					fonts;
	t_btn					btnarr[20];
	t_btn					btnmap[100];
	t_btn					btnopt[20];
	t_btn					btnpse[20];
	t_slid					slidopt[10];
	t_slid					*currslid;
	t_menu_status			m_status;
	t_btn					*curr_btn;
	t_pal					fire;
	SDL_Texture				*weaponhud[NB_WEAPON];
	SDL_Texture				*sprites[ENDSPRITES + 1];
	SDL_Texture				*props[MAXPROPSNUMBER + MAXWPROPSNUMBER + 1];
	SDL_Surface				*propssurf[MAXPROPSNUMBER + MAXWPROPSNUMBER + 1];
	SDL_Surface				*enemy[ENEMYTXTRTOTAL];
}							t_ui;

/*
** 0 : Window is closed
** 1 : Textures are loading
** 2 : Textures are loaded
** 3 : Writing
** 4 : Int to forme // Turned off
** 5 : Writing to save file
** 6 : Writing to load file
*/

typedef enum				e_editorstatus
{
	ED_CLOSED,
	ED_LOADING,
	ED_LOADED,
	ED_WRITING,
	ED_SAVING,
	ED_OPEN,
}							t_editorstatus;

/*
**	ED_FORME
*/

typedef struct				s_editor
{
	t_editorstatus			status;
	t_selecttxtr			selecttxtr;
	SDL_Window				*win;
	SDL_Renderer			*rend;
	t_ui					*ui;
	t_vct2					size;
	t_vct2					mouse;
	t_vct2					mapmouse;
	int						sectscroll;
	int						txtrscroll;
	SDL_Rect				sectbox;
	SDL_Rect				optbox;
	SDL_Rect				txtrbox;
	t_tab					keys;
	t_pilier				*currpilier;
	t_ecoord				*currstat;
	t_mur					*currmur;
	int						*currwriter;
	t_pilier				*hoverpilier;
	t_mur					*hovermur;
	t_lstsec				map;
	t_vct3					mappos;
	t_eplayer				player;
	t_lstpil				pillist;
	t_lstent				ennlist;
	t_lstsec				sectors;
	SDL_Texture				*txtrgame[MAXTXTRNUMBER];
	SDL_Texture				*txtrreal[MAXTXTRNUMBER];
	SDL_Texture				*sprites[MAXPROPSNUMBER];
	SDL_Texture				*wsprites[MAXWPROPSNUMBER];
	char					*txtrname[MAXTXTRNUMBER];
	char					filename[MAXFILENAMELEN];
}							t_editor;

/*
** Editor
*/

unsigned int				ft_lil_super_atoi(const char *str);

int							write_hook(t_doom *doom, char *str
	, SDL_KeyboardEvent e);
void						draw_writer(t_editor *edit);

int							save_editor_to_file(t_editor *edit);

t_btn						add_test_button(t_editor *edit, SDL_Rect *parent);

int							editor_key_press(int key, t_doom *doom);
int							editor_key_release(int key, t_doom *doom);
int							editor_mouse_press(SDL_MouseButtonEvent e
	, t_editor *edit);

int							editor_mouse_move(SDL_MouseMotionEvent e
	, t_editor *edit);
int							editor_mouse_wheel(SDL_MouseWheelEvent e
	, t_editor *edit);

/*
** get_rel_map_pos to check all
*/

t_vct2						g_r_mp(t_editor *editor, int x, int y);

void						draw_map(t_editor *editor);
void						draw_sector_menu(t_editor *editor, t_font font);
void						draw_inspect_menu(t_editor *editor);

void						remove_ptr_from_map(t_lstsec lstsec
	, t_lstent lstent, void *ptr);

void						sector_menu(t_editor *edit, int pos, int del);
int							ft_walllen(t_lstmur start);
void						ft_remove_walls_with_pillar(t_editor *edit
	, t_lstmur *start, t_pilier *pil);
void						ft_removewall(t_editor *edit, t_lstmur *start
	, t_mur **mur);
void						ft_movewall(t_mur *wall, int addx, int addy
	, int zoom);
t_lstmur					ft_wallpushend(t_lstmur *start, t_pilier *pil1
	, t_pilier *pil2, SDL_Texture *txtr);
void						ft_clear_wall_list(t_lstmur *start);
t_secteur					*sector_menu_click(t_editor *edit, int pos
	, int cas);
int							opt_menu_click(t_editor *edit, int pos);
int							opt_menu_wheel(SDL_MouseWheelEvent e
	, t_editor *edit);
SDL_Texture					*txtr_menu_click(t_editor *edit, int x, int y
	, int max);
int							txtr_menu_click_int(t_editor *editor, t_vct2 m
	, int min, int max);
int							texturebox_click(t_editor *edit
	, SDL_MouseButtonEvent e);
t_mur						*find_mur(t_editor *editor, t_lstsec start, int x
	, int y);
t_lstpil					ft_newpillar(t_vct2 loc);
void						ft_movepillar(t_lstsec sectors, t_pilier *pil
	, t_vct2 add, int zoom);
void						ft_removepillar(t_lstpil *start, t_lstpil *pil);
t_lstpil					ft_pillarpushend(t_lstpil *start, t_vct2 loc);
void						ft_clear_pillar_list(t_lstpil *start);
void						ft_nodeprint_pillar(t_lstpil node);
t_lstpil					find_pilier(t_editor *editor, t_lstpil start
	, int x, int y);
t_ecoord					*find_player(t_editor *edit, int x, int y);

int							add_pillar(t_editor *edit, int x, int y);

t_lstsec					ft_newsector(SDL_Texture *top, SDL_Texture *sol);
t_lstsec					push_secteur(t_lstsec *node, SDL_Texture *top
	, SDL_Texture *sol);
void						ft_remove_pillar_from_sector(t_editor *edit
	, t_lstsec sectors, t_lstpil *start, t_lstpil *pil);
void						ft_clear_secteur(t_lstsec *sec);
void						ft_clear_secteur_list(t_lstsec *start);

t_entity					*ft_newenemy(t_vct2 loc, int type
	, t_secteur *sctr);
void						ft_removeenemy(t_lstent *start, t_entity **pil);
t_entity					*ft_enemypushend(t_lstent *start, t_vct2 loc
	, int type, t_secteur *sctr);
void						ft_removeenemywithstat(t_lstent *start
	, t_ecoord **pil);
void						ft_clear_entity_list(t_lstent *start);

t_vct2						line_percent(t_vct2 pos1, t_vct2 pos2
	, double percent);
void						scroll_limits(int *value, int addition, int smin
	, int smax);

t_vct2						get_screen_mappos(t_editor *editor, int x, int y);
t_vct2						g_r_mp(t_editor *editor, int x, int y);

/*
**	parsing
*/

int							editor_init(t_editor *editor);
int							read_file_to_editor(t_editor *edit
	, const char *file);

/*
**	editor_manager
*/

int							editor_reset(t_editor *editor);
void						ui_free(t_ui *ui);
int							load_weapons(t_doom *doom, t_ui *ui);
int							link_txtr(t_doom *doom, t_ui *ui);
int							ui_init(t_ui *ui);

#endif
