/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:39:33 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 17:17:26 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "sector.h"
# include "player.h"
# include "editor.h"
# include "architect.h"

typedef struct s_doom	t_doom;
typedef struct s_enemy	t_enemy;
typedef struct s_sector	t_sector;
typedef struct s_wall	t_portal;
typedef struct s_prop	t_prop;

/*
** Define checker
*/

# define ISENEMY(x) (MINENEMYPOS <= x && x < MAXENEMYPOS)
# define ISPROP(x) (MINPROPSPOS <= x && x < MAXPROPSPOS)
# define ISWALLPROP(x) (MINWPROPSPOS <= x && x < MAXWPROPSPOS)
# define ISPORTAL(x) (x >= WINDOW)

enum					e_window_id
{
	DOOM_WINDOW = 1,
	EDITOR_WINDOW = 2
};

typedef struct			s_slen
{
	int					nb_pills;
	int					nb_txtrs;
	int					nb_sects;
	int					current_sector;
}						t_slen;

typedef struct			s_sound
{
	Mix_Chunk			*e_world;
	Mix_Chunk			*e_perso;
	Mix_Chunk			*e_other;
	Mix_Chunk			*tab_effect[50];
	Mix_Music			*music;
	Mix_Music			*tab_music[11];
	int					on;
	int					maxmusic;
	int					musicvolume;
	int					effectvolume;
}						t_sound;

typedef struct			s_minimap
{
	t_vct2				d;
	t_vct2				a;
	t_vct2				size;
	t_vct2				mid;
	t_sdl				*sdl;
	t_ui				*ui;
}						t_minimap;

typedef enum			e_difficulty
{
	EASY = 1,
	MEDIUM = 2,
	HARD = 4
}						t_difficulty;

typedef struct			s_game
{
	t_slen				len;
	t_player			player;
	t_sound				sound;
	t_sector			*sectors;
	t_pillar			*pillars;
	SDL_Surface			**gamesurf;
	char				**surfpath;
	t_arch				arch;
	t_ui				*ui;
	t_camera			camera;
	t_difficulty		difficulty;
}						t_game;

struct					s_doom
{
	int					debug;
	t_sdl				sdl;
	t_editor			edit;
	t_ui				ui;
	Uint32				timestamp;
	SDL_GameController	*controller;
	t_game				game;
};

/*
**	manager
*/

void					doom_exit(t_doom *doom);
t_doom					*doom_init();
int						parsing(t_doom *doom, char *filename);
void					fire_init(t_doom *doom);
void					fire(t_pal *fire);
void					fire_on_off(Uint32 *screen, t_vct2 size, int status);
void					btn_click(t_doom *doom, int x, int y);
t_btn					add_start_button(t_doom *doom);
t_btn					add_mapmenu_button(t_doom *doom);
t_btn					add_map_button(t_doom *doom, const char *str);
t_btn					add_pause_button(t_doom *doom);
t_btn					add_left_music_button(t_doom *doom, SDL_Rect *parent);
t_btn					add_middle_music_button(t_doom *doom);
t_btn					add_right_music_button(t_doom *doom, SDL_Rect *parent);
t_btn					add_left_diff_button(t_doom *doom, SDL_Rect *parent);
t_btn					add_middle_diff_button(t_doom *doom, SDL_Rect *parent);
t_btn					add_right_diff_button(t_doom *doom, SDL_Rect *parent);
SDL_Texture				*add_fist(t_doom *doom);
SDL_Texture				*add_handgun(t_doom *doom);
SDL_Texture				*add_shotgun(t_doom *doom);
SDL_Texture				*add_rifle(t_doom *doom);
t_btn					add_resume_button(t_doom *doom);
t_btn					add_doom_button(t_doom *doom, const char *name);
t_btn					add_opt_button(t_doom *doom);
t_btn					add_ing_opt_button(t_doom *doom);
t_btn					add_main_menu_button(t_doom *doom);
t_btn					add_editor_button(t_doom *doom);
t_btn					add_quit_button(t_doom *doom, const char *str,
																void *fc);
int						sdl_set_status(t_doom *doom, t_menu_status status);
void					draw_menu(t_doom *doom);
int						load_map_btns(t_doom *doom);
void					update_loc(t_vct2 size, t_sloc *loc, SDL_Rect before);
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
int						game_key_press(int key, t_doom *doom);
void					key_press(int key, t_doom *doom);
int						key_release(int key, t_doom *doom);
int						mouse_press(int button, int x, int y, t_doom *doom);
int						mouse_release(int button, int x, int y, t_doom *doom);
int						mouse_wheel(SDL_MouseWheelEvent e, t_doom *doom);
int						mouse_move(int x, int y, t_doom *doom);
void					print_image(SDL_Surface *png);
unsigned int			color_rgb(uint8_t r, uint8_t g, uint8_t b);
void					*listdel(t_list **list);
char					**tab_new(int y);
void					controller_handler(t_doom *doom, t_player *player
	, SDL_Event event);
void					lst_del_node(t_list **node);
void					open_editor(t_doom *doom);
int						close_editor(t_doom *doom);
int						secure_doom(t_doom *doom);

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
void					set_easy(t_doom *doom);
void					set_medium(t_doom *doom);
void					set_hard(t_doom *doom);

/*
**	simple input
*/

void					game_over(t_doom *doom, bool win);
void					pickup_prop(t_doom *doom);
void					action(t_doom *doom, t_stat *s, t_inv *inv);
void					kick(Uint32 timestamp, t_sound *sound, t_player *pl
	, t_stat *s);
void					debug_up(t_doom *doom);
void					calcdelay(const char *str, t_doom *doom);
int						pos_in_rect(SDL_Rect rect, int x, int y);
void					point_gras(t_vct2 cursor, Uint32 color, t_doom *doom);
t_wall					*collision(t_sector *sector, t_fvct3 pos, t_wall *w);
t_wall					*colli_walls(t_sector *sector, t_fvct3 ori, t_fvct3 pos
	, t_wall *w);
int						colli_port(t_stat *stat, t_sector *sector, t_fvct3 ori
	, t_wall **wall);
int						vector_intersect(t_fvct3 p1, t_fvct3 q1, t_fvct3 p2
	, t_fvct3 q2);

/*
**	editor_input
*/

void					editor_loop_hook(t_doom *doom);
int						editor_key_press(int key, t_doom *doom);
int						editor_key_release(int key, t_doom *doom);
int						ui_by_sdl(t_doom *doom, t_ui *ui);
void					outgame_loop_hook(t_doom *doom);
void					armandtificial_intelligence(t_doom *doom);
int						hud_render(t_doom *doom);
int						doom_render(t_doom *doom);
void					bold_point(t_vct2 v, Uint32 color, t_doom *doom);
void					sector_set_box(t_sector *sector);

/*
** Artificial intelligence
*/

void					update_enemy_rotation(t_enemy *enemy, t_stat *s
	, t_fvct3 pos);
bool					is_between(t_fvct3 pos, t_fvct3 target, t_fvct3 m1
	, t_fvct3 m2);
int						is_visible(t_stat *stat, t_stat *target
	, t_sector *sector, int passed);
void					is_around_recur(t_doom *d, t_sector **passed
	, t_sector *s, int *index);
void					is_around(t_doom *d, t_sector *s, t_sector **passed
	, int *index);
bool					is_passed(t_sector *sector, t_sector **passed
	, int index);
void					ai_active(t_doom *d, t_enemy *t, t_sector *s);

#endif
