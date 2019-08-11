/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/08/10 22:18:43 by akrache          ###   ########.fr       */
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
//le bunch permet de faire des groupe de mur visible
//pour organiser l'affichage
//over : indique si le mur depasse la vision mais et relier a un
//mur dans la vision
# define JOYSTICK_DEAD_ZONE 5000
# define SENSIBILITY 6.0

/*
** Editor Stuff
*/
# define EDPADDING 5
# define EDITORPRECISION 5000
# define DEBUG 0
# define SECTORBOXHEIGHT 50
# define MAXEDITVAR 999999
#define MINZOOM 10
#define MAXZOOM 20000
#define ZOOMSPEED 3

/*
**	gestion
*/
void					updateText(SDL_Renderer *rend, TTF_Font *font, SDL_Texture **text, SDL_Rect *loc, const char *str, SDL_Color fg, SDL_Color bg);
void					dropfile_event(t_doom *doom, SDL_Event e);


int						load_textures_folder(SDL_Renderer *rend, SDL_Texture **txtrs, char **txtrsname);
void					free_textures_folder(SDL_Texture **txtrs, char **txtrsname);
void					editor_free(t_doom *doom);

/*
**	parsing
*/

int						read_file(t_game *game, const char *file, bool foredit);

int						check_file(const char *file);
void					free_game(t_game *game);

/*
**	debug
*/
void					move_input(t_doom *doom, int key);
void					mvt_input(t_player *player, int key);
void					move(t_stat *stat, t_inv *inv);
void					bold_point(t_vct2 cursor, Uint32 color, t_doom *doom);
void					PrintEvent(const SDL_Event *event);
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
void					mini_draw_wall(t_wall *wall, t_fvct3 pos, t_minimap *mini);
int						bold_point2(t_minimap *mini, t_vct2 pos, Uint32 color);
void					minibord(t_minimap *mini);
void					miniwalls(t_player *player, t_sector *sector, t_minimap *mini);
void					miniinv(t_minimap *mini, t_player *player);

/*
** HUD
*/
void					hud_aim(t_doom *doom);
int						hud_render(t_doom *doom);
int						doom_render(t_doom *doom);

#endif
