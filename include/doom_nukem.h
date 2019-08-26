/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/08/26 17:24:41 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "input.h"
# include "calcul.h"

# define RADIUS 500
# define TOTALMUSIC 11

# define UNIT 8.0

# define DECELERATION 2500.0
# define PADDING 0.30
# define PADDING2 0.60
# define STEP 0.5
# define HITBOXSIZE 0.5
# define TTFWOLF "ressources/font/wolfenstein.ttf"
# define TTFIMPACT "ressources/font/impact.ttf"
# define MAX_FAR 10000
# define JOYSTICK_DEAD_ZONE 5000
# define SENSIBILITY 6.0

/*
** Editor Stuff
*/

# define NBTXTRBYLINE 5
# define TXTRSIZE 125
# define EDPADDING 5
# define EDITPREC 5000
# define DEBUG 0
# define SBH 50
# define MAXEDITVAR 999999
# define MINZOOM 10
# define MAXZOOM 20000
# define ZOOMSPEED 3

/*
**	gestion
*/

typedef struct			s_updatetext {
	SDL_Renderer		*rend;
	TTF_Font			*font;
	SDL_Texture			**text;
	SDL_Rect			*loc;
	const char			*str;
	SDL_Color			fg;
	SDL_Color			bg;
}						t_updatetext;

void					updatetext(t_updatetext t);
void					dropfile_event(t_doom *doom, SDL_Event e);
int						asynchronous_txtr_load(void *param);
void					free_textures_folder(SDL_Texture **txtrs
	, char **txtrsname);
void					editor_free(t_doom *doom);
int						sdl_draw_filename(t_editor *edit, const char *text);
int						try_save(t_doom *doom, SDL_KeyboardEvent e);
void					push_char(char *str, char c);

/*
** Editor render
*/

void					map_draw_line(t_editor *editor, t_vct2 pos0
	, t_vct2 pos1, SDL_Color c);
void					draw_grid(t_editor *editor, t_vct2 center
	, int dist, int master);
void					draw_player(t_editor *editor);
void					draw_props(t_editor *editor, t_entity *curr
	, SDL_Texture **sprites, int proppos);
void					draw_enemies(t_editor *editor, t_entity *curr);
void					draw_objs(t_editor *editor, t_entity *start);
void					draw_one_wall(t_editor *editor, t_lstmur currwall);
void					norm_draw_walls(t_editor *editor, t_lstsec currsec);

/*
**	parsing
*/

void					write_balise(int fd, char *balise);
void					write_one_wall(int fd, t_lstmur wall);
void					write_sec_walls(int fd, t_lstmur wall);
void					write_sec_props(int fd, t_secteur *sect
	, t_lstent props);
void					write_sectors(int fd, t_editor *edit);
void					write_wall_props(int fd, t_lstent props);
void					write_pillars(int fd, t_editor *edit);
void					write_one_prop(int fd, t_entity *prop);
void					write_one_sector(int fd, t_secteur *sec
	, t_lstent props);
void					write_one_enemy(int fd, t_entity *enn);
void					write_player(int fd, t_eplayer *player);
char					*get_path(t_editor *edit, SDL_Texture *txtr);
void					load_used_textures(t_editor *edit);
int						push_texture(t_editor *edit, SDL_Texture *txtr);
int						read_one_texture(int fd, SDL_Surface **surf
	, char **sp);
int						read_textures(int fd, SDL_Surface ***surf
	, t_slen *len, char ***sp);
int						read_one_pillar(int fd, t_pillar *pill);
int						read_pillars(int fd, t_pillar **pillars, t_slen *len);
int						read_one_prop(int fd, t_game *game, t_prop *prop
	, t_slen *len);
int						read_one_wall(int fd, t_game *game, t_wall *wall
	, t_slen *len);
int						read_wall_props(int fd, t_game *game, t_wall *wall
	, t_slen *len);
int						read_sec_walls(int fd, t_game *game, t_sector *sector
	, t_slen *len);
int						read_sec_props(int fd, t_game *game, t_sector *sector
	, t_slen *len);
int						read_balise(int fd, char *balise, int ret);
int						read_one_sector(int fd, t_game *game, t_sector *sector
	, t_slen *len);
int						read_sectors(int fd, t_game *game, t_slen *len);
SDL_Texture				*find_texture(SDL_Texture **txtrs, char **edpath
	, char *surfpath);
t_secteur				*find_secteur(t_lstsec secteurs, t_game *g
	, t_sector *sector);
t_mur					*find_mur_in_secteur(t_lstsec secteurs, t_game *g
	, t_wall *wall);
void					fill_ent(t_lstsec secteurs, t_game *g, t_entity *ent
	, t_prop *prop);
int						relink_sector(t_game *g, t_editor *e);
void					add_walls(t_game *g, t_editor *e, t_sector *gsec
	, t_secteur *sec);
void					add_wall_prop(t_game *g, t_editor *e, t_wall *gamewall
	, t_mur *mur);
t_pilier				*find_pillar_from_game(t_pillar *pillars
	, t_pillar *to_find, t_lstpil pillst);
void					set_txtr(t_txtr *txtr, SDL_Surface *surf, int id);
int						read_file(t_game *game, const char *file
	, bool foredit);
int						check_balise(int fd, char *balise, int ret);
int						check_pillars(int fd, t_slen *len);
int						check_sec_props(int fd);
int						check_sec_walls(int fd, t_slen *len);
int						check_sectors(int fd, t_slen *len);
int						check_enemies(int fd);
int						check_file(const char *file);
void					free_game(t_game *game);
int						game_to_editor(t_game *g, t_editor *e);

/*
**	debug
*/

void					move_input(t_doom *doom, int key);
void					mvt_input(t_player *player, int key);
void					move(t_stat *stat, t_inv *inv);
void					bold_point(t_vct2 cursor, Uint32 color, t_doom *doom);
int						keyboard_input(t_doom *doom, SDL_Event event);
void					play_effect(t_sound *sound, int e);

/*
**	Cinematique et Musique
*/

void					concat_atoi(char *str, int i);
void					cine_events(t_doom *doom, int *i);
void					prev_track(t_doom *doom);
void					next_track(t_doom *doom);
void					effect_free(t_sound *sound);
int						effect_init(t_sound *sound);
void					music_free(t_sound *sound);
int						music_init(t_sound *sound);
void					change_music(t_sound *sound, int n, int fade);
void					cinematrique(t_doom *doom);
void					effect_volume(t_sound *sound);

/*
** Minimap
*/

void					minimap(t_minimap *mini, t_player *player);
t_minimap				miniinit(t_sdl *s, t_ui *ui);
void					mini_draw_wall(t_wall *wall, t_fvct3 pos
	, t_minimap *mini);
int						bold_point2(t_minimap *mini, t_vct2 pos, Uint32 color);
void					minibord(t_minimap *mini);
void					miniwalls(t_player *player, t_sector *sector
	, t_minimap *mini);
void					miniinv(t_minimap *mini, t_player *player);
void					minifield(t_player *player, t_minimap *mini);
void					minifill(t_minimap *m, int h, t_power p);

/*
** HUD
*/

void					hud_aim(t_doom *doom);
int						hud_render(t_doom *doom);
int						doom_render(t_doom *doom);

/*
** Gameplay
*/

void					open_close(t_prop *prop);
void					end_level(t_doom *doom);
void					func_prop(t_prop *prop, int type);
void					addkey1(t_inv *inv);
void					addkey2(t_inv *inv);
void					addkey3(t_inv *inv);
void					addlastkey(t_inv *inv);
void					heal(t_stat *stat);
void					add_ammo(t_weapon *weapon);
void					new_music(t_sound *sound);
void					add_weapon(t_weapon *weapon);
void					jetpack(t_inv *inv);

#endif
