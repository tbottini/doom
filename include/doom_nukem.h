/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/06/21 12:54:41 by tbottini         ###   ########.fr       */
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
# include <SDL_mixer.h>
# include <limits.h>
# include "sector.h"
# include "player.h"
# include "calcul.h"
# include "doom_struct.h"

# define MINWIDTH 800
# define MINHEIGHT 800
# define WIDTH 1280
# define HEIGHT 800
# define MAXWIDTH 1920
# define MAXHEIGHT 1080
# define PI 3.1415926535897932
# define PI180 0.01745329251
# define TOANGLE 57.2957795131

/*
**	Color
*/
# define BLUE_SKY 0x4559a8ff
# define RED_WALL 0xb30000ff
# define PINK_FLOOR 0xdcc8c8ff

# define ACCELERATION 5000.0
# define DECELERATION 2500.0
# define TTFWOLF "ressources/font/wolfenstein.ttf"
# define TTFIMPACT "ressources/font/impact.ttf"
# define MAX_FAR 10000
//le bunch permet de faire des groupe de mur visible
//pour organiser l'affichage
//over : indique si le mur depasse la vision mais et relier a un
//mur dans la vision
# define JOYSTICK_DEAD_ZONE 5000
# define SENSIBILITY 6.0

/*
** Editor Stuff
*/
#define MAXZOOM 20000
# define EDITORPRECISION 10000
# define DEBUG 0

/*
** Button Functions
*/

void					start_button(t_doom *doom);
void					resume_button(t_doom *doom);
void					start_map_button(t_doom *doom);
void					option_button(t_doom *doom);
void					ignoption_button(t_doom *doom);
void					main_menu_button(t_doom *doom);
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
t_btn					add_pause_button(t_doom *doom);
t_btn					add_left_music_button(t_doom *doom, t_sloc *parent);
t_btn					add_middle_music_button(t_doom *doom);
t_btn					add_right_music_button(t_doom *doom, t_sloc *parent);
t_btn					add_resume_button(t_doom *doom);
t_btn					add_doom_button(t_doom *doom, const char *name);
t_btn					add_opt_button(t_doom *doom);
t_btn					add_ing_opt_button(t_doom *doom);
t_btn					add_main_menu_button(t_doom *doom);
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
t_slid					add_music_slider(t_doom *doom);
t_slid					add_effect_slider(t_doom *doom);
void					draw_slid(t_doom *doom, t_slid *tmp);
int						event_handler(t_doom *doom);
int						event_handler_doom(t_doom *doom, SDL_Event event);
int						event_handler_editor(t_doom *doom, SDL_Event event);
int						loop_hook(t_doom *doom);
t_btn					*btn_hover(t_doom *doom, int x, int y);
void					draw_hover(t_doom *doom, t_btn *newl, t_btn *old);

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

/*
** Drawer functions
*/

int						sdl_string_put(SDL_Renderer *rend, TTF_Font *font, t_vct2 loc, const char *text, SDL_Color fg);
int						sdl_int_put(SDL_Renderer *rend, TTF_Font *font, t_vct2 loc, const char *label, const int value, SDL_Color fg);
void					sdl_cleartexture(Uint32 *screen, t_vct2 size);
void					big_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
int						fill_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
//void					editor_fill_line(t_editor *ed, t_vct2 pos0, t_vct2 pos1, Uint32 color);
void					fill_line(t_sdl *sdl, t_vct2 pos0, t_vct2 pos1, Uint32 color);

/*
** Editor
*/

int						editor_key_press(int key, t_doom *doom);
int						editor_key_release(int key, t_doom *doom);
int						editor_mouse_press(SDL_MouseButtonEvent e, t_editor *edit);
int						editor_mouse_release(int button, int x, int y,
																t_doom *doom);
int						editor_mouse_move(SDL_MouseMotionEvent e, t_doom *doom);
int						editor_mouse_wheel(SDL_MouseWheelEvent e, t_editor *edit);

t_vct2					get_rel_mappos(t_editor *editor, int x, int y);

void					draw_map(t_editor *editor);
void					draw_sector_menu(t_editor *editor, t_font font);

void					sector_menu_click(t_editor *edit, int pos, int del);

void					ft_remove_pillar_fromwalls(t_lstmur *start, t_pilier *pil);
t_lstmur 				ft_wallpushend(t_lstmur *start, t_pilier *pil1, t_pilier *pil2);
int						ft_walllen(t_lstmur start);
void					ft_clear_wall_list(t_lstmur *start);

t_lstpil				ft_newpillar(t_vct2 loc);
void					ft_removepillar(t_lstpil *start, t_lstpil *pil);
t_lstpil				ft_pillarpushend(t_lstpil *start, t_vct2 loc);
void					ft_clear_pillar_list(t_lstpil *start);
void					ft_nodeprint_pillar(t_lstpil node);
void 					ft_nodeprint_secteur(t_lstsec node);
t_lstpil				find_pilier(t_editor *editor, t_lstpil start, int x, int y);

int						add_pillar(t_editor *edit, int x, int y);

t_lstsec				ft_newsector();
t_lstsec				push_secteur(t_lstsec *node);
void					ft_remove_pillar_from_sector(t_lstsec sectors, t_lstpil *start, t_lstpil *pil);
void					ft_clear_secteur(t_lstsec *sec);
void					ft_clear_secteur_list(t_lstsec *start);

/*
**	gestion
*/

void					updateText(SDL_Renderer *rend, TTF_Font *font, SDL_Texture **text, SDL_Rect *loc, const char *str, SDL_Color fg, SDL_Color bg);
void					dropfile_event(t_doom *doom, SDL_Event e);
void					doom_exit(t_doom *doom);
t_doom					*doom_init();
int						designer_init(t_designer *designer, t_sdl *sdl, t_camera *cam);
void					editor_free(t_editor *editor);
int						editor_init(t_editor *editor);
void					sdl_free(t_sdl *sdl);
int						sdl_init(t_sdl *sdl, const char *title);
void					ui_free(t_ui *ui);
int						ui_init(t_ui *ui);
int						ui_by_sdl(t_doom *doom, t_ui *ui);

void					wall_screen_info(t_designer *arch, t_player *p);

/*
**	simple input
*/

void					bullet(t_doom *doom, t_stat *stat);
void					action(t_player *player, t_stat *stat);
void					kick(t_doom *doom, t_player *player);
void					PrintEvent(const SDL_Event *event);
void					debug_up(t_doom *doom);
void					sdl_MultiRenderCopy(t_sdl *sdl);
void					calcdelay(const char *str, t_doom *doom);
int						pos_in_rect(SDL_Rect rect, int x, int y);

void					point_gras(t_vct2 cursor, Uint32 color, t_doom *doom);
void					trait(t_doom *doom, t_vct2 vct1, t_vct2 vct2, Uint32 col);
double					distance(t_fvct2 vct1, t_fvct2 vct2);
t_wall					*collision(t_stat *stat, t_fvct3 pos, t_wall *w);
t_wall					*collisionV21(t_stat *stat, t_fvct3 ori, t_fvct3 pos, t_wall *w);
int						vector_intersect(t_fvct3 p1, t_fvct3 q1, t_fvct3 p2, t_fvct3 q2);
void					bulletV42(t_doom *doom, t_player *player);

/*
**	parsing
*/

t_wall					*chunck_walls(t_list *chunck_line, t_designer *ressources, size_t len);
int						chunk_texture(t_sdl *sdl, t_designer *designer, int fd);
t_player				chunck_player(int fd);
t_sector				*chunck_sector(int fd, t_designer *ressources);
t_sector				*sector_new();
t_list					*ft_lstn(void *content);

/*
**	debug
*/
void					move_input(t_doom *doom, int key);
void					mvt_input(t_player *player, int key);
void					move(t_stat *stat);
void					bold_point(t_vct2 cursor, Uint32 color, t_doom *doom);
void					draw_wall(t_designer *arch, t_player *player);
void					minimap(t_doom *d);
void					PrintEvent(const SDL_Event *event);
int						keyboard_input(t_doom *doom, SDL_Event event);
void					play_effect(t_sound *sound, int e);

/*
**	render
*/
int						z_line_buffer(t_designer *arch, double len_pillar, int px);
int						doom_render(t_doom *doom);
void					zline_reset(t_designer *arch);
int						fish_bowl_px(t_designer *arch, t_pillar pillar);
void					fish_eyes(double *dist, double angle);
double					wall_clipping(t_designer *arch, t_wall *wall, t_fvct2 pos, double angle);
uint32_t				texture_interpolation2D(t_designer *arch);

/*
**	bunch
*/
void					sector_frustum(t_sector *sector, t_player player);
int						buncherisation(t_sector sector, t_wall **bunch);
void					bunch_comsuption(t_doom *doom, t_wall **bunch, t_sector *sector);

/*
**	Cinematique et Musique
*/

void					prev_track(t_doom *doom);
void					next_track(t_doom *doom);
void					effect_free(t_sound *sound);
int						effect_init(t_sound *sound);
void					music_free(t_sound *sound);
int						music_init(t_sound *sound);
void					change_music(t_sound *sound, int n, int fade);
void					cinematrique(t_doom *doom);
void					effect_volume(t_sound *sound);

#endif
