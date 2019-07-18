/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:57:52 by magrab            #+#    #+#             */
/*   Updated: 2019/07/17 17:39:23 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <stdbool.h>
# include "render.h"
# include "editor.h"
# include "input.h"
# include "debug.h"

/*
**		!!! global de debug a enlever
*/
extern int debug;

# define DEBUG_VISUAL 1

# define MINWIDTH 800
# define MINHEIGHT 800
# define EDITMINWIDTH 1024
# define EDITMINHEIGHT 800
# define MAXWIDTH 1920
# define MAXHEIGHT 1080
# define PI 3.1415926535897932
# define PI180 0.01745329251
# define TOANGLE 57.2957795131

# define RADIUS 500
# define TOTALMUSIC 10

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
# define EDPADDING 5
# define MAXZOOM 20000
# define EDITORPRECISION 5000
# define DEBUG 0
# define SECTORBOXHEIGHT 50
# define MAXEDITVAR 999999

/*
**	gestion
*/

void					updateText(SDL_Renderer *rend, TTF_Font *font, SDL_Texture **text, SDL_Rect *loc, const char *str, SDL_Color fg, SDL_Color bg);
void					dropfile_event(t_doom *doom, SDL_Event e);
void					doom_exit(t_doom *doom);
t_doom					*doom_init();
int						designer_init(t_arch *designer, t_sdl *sdl, t_camera *cam);
int						load_textures_folder(SDL_Renderer *rend, SDL_Texture **txtrs, char **txtrsname);
void					free_textures_folder(SDL_Texture **txtrs, char **txtrsname);
void					editor_free(t_doom *doom);
int						arch_init(t_arch *arch, t_sdl *sdl, t_camera *cam);
int						editor_init(t_editor *editor);
void					sdl_free(t_sdl *sdl);
int						sdl_init(t_sdl *sdl, const char *title);
void					ui_free(t_ui *ui);
int						ui_init(t_ui *ui);
int						ui_by_sdl(t_doom *doom, t_ui *ui);

/*
**	parsing
*/

int						read_file(t_game *game, const char *file);
int						read_file_to_editor(t_editor *edit, const char *file);
int						check_file(const char *file);
void					free_game(t_game *game);

t_wall					*chunck_walls(t_list *chunck_line, t_arch *ressources, size_t len);
int						chunk_texture(t_sdl *sdl, t_arch *arch, int fd);
t_player				chunck_player(int fd);
t_sector				*chunck_sector(int fd, t_arch *ressources);
t_sector				*sector_new();
t_list					*ft_lstn(void *content);
int						line_wall(t_arch *rsrc, t_wall *wall, char *line);

/*
**	debug
*/
void					move_input(t_doom *doom, int key);
void					mvt_input(t_player *player, int key);
void					move(t_stat *stat);
void					bold_point(t_vct2 cursor, Uint32 color, t_doom *doom);
void					minimap(t_doom *d);
void					PrintEvent(const SDL_Event *event);
int						keyboard_input(t_doom *doom, SDL_Event event);
void					play_effect(t_sound *sound, int e);

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

/*
** Minimap
*/

int						bold_point2(t_minimap mini, t_vct2 pos, Uint32 color);
void					minibord(t_doom *d, t_minimap mini);
void					miniwalls(t_doom *doom, t_sector *sector, t_minimap mini);

#endif
