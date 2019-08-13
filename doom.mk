SRCS_DOOM		:=		button_function.c								\
						slider_function.c								\
						main.c											\
						checkfile.c										\
						cinematri.c										\

SRCS_EDITOR		:=		draw_inspect_menu.c								\
						draw_sector_menu.c								\
						editor_finder.c									\
						editor_input.c									\
						editor_key.c									\
						editor_menu_wheel.c								\
						editor_mouse_move.c								\
						editor_mouse_press.c							\
						editor_mouse_wheel.c							\
						editor_optionbox.c								\
						editor_render_draw.c							\
						editor_render.c									\
						editor_txtrbox.c								\
						editor_write.c									\

SRCS_UI			:=		button_action.c									\
						button_drawer.c									\
						button_hover.c									\
						button_loader.c									\
						init_btns_edit.c								\
						init_btns.c										\
						init_btns2.c									\
						init_btns3.c									\
						init_btns4.c									\
						init_slids.c									\
						init_textures.c									\
						fire.c											\


SRCS_GAMEPLAY	:=		action.c										\
						move.c											\
						move2.c											\
						weapons.c										\
						shoot.c											\
						shooting.c										\
						shoot_tools.c									\
						collision.c										\
						gameover.c										\
						ia.c											\
						ia_tools.c										\
						ia_action.c										\

SRCS_INPUT		:=		event_controller.c								\
						event_handler.c									\
						event_handler_doom.c							\
						event_handler_editor.c							\
						input_hook.c									\
						loop_hook.c										\
						debug_input.c									\

SRCS_RENDER		:=		render.c										\
						sector.c										\
						hud_render.c									\
						hud/minimap.c									\
						hud/minimap_drawer.c							\
						pre_render/backface.c							\
						pre_render/render_effect.c						\
						pre_render/bunch.c								\
						pre_render/wall.c								\
						pre_render/borne.c								\
						pre_render/pillar_info.c						\
						drawer/render_wall.c							\
						drawer/textures.c								\
						drawer/draw_line.c								\
						drawer/draw_text.c								\
						drawer/draw_column.c							\
						render_enemy.c									\
						sprite.c										\
						prop.c											\

SRCS_PARSING	:=		lil_savefile.c									\
						readfile.c										\
						readfileeditor.c								\
						savefile.c										\
						super_savefile.c								\

SRCS_TOOLS		:=		list_tools.c									\
						editor_tools.c									\
						entity_tools.c									\
						file_tools.c									\
						mur_tools.c										\
						norm_tools.c									\
						little_tools.c									\
						num_tools.c										\
						sdl_tools.c										\
						secteur_tools.c									\
						play_tools.c									\
						savefile_tools.c								\
						musi.c											\
						vector.c										\
						editor_write_tools.c							\

SRCS_GESTION	:=		doom_manager.c									\
						sdl_manager.c									\
						ui_manager.c									\
						player_manager.c								\
						editor_manager.c								\
						music_manager.c									\
						effect_manager.c								\
						weapon_manager.c								\
						enemy_manager.c									\
						prop_manager.c									\
						arch_manager.c									\
						borne_manager.c									\
						camera_manager.c								\

SRCS_CALCUL		:=		affine.c										\
						extra_calcul.c									\

OBJS			:=		$(patsubst %.c,objs/%.o,$(SRCS_DOOM))			\
						$(patsubst %.c,objs/render/%.o,$(SRCS_RENDER))	\
						$(patsubst %.c,objs/parsing/%.o,$(SRCS_PARSING))\
						$(patsubst %.c,objs/debug/%.o,$(SRCS_DEBUG))	\
						$(patsubst %.c,objs/tools/%.o,$(SRCS_TOOLS))	\
						$(patsubst %.c,objs/ui/%.o,$(SRCS_UI))			\
						$(patsubst %.c,objs/input/%.o,$(SRCS_INPUT))	\
						$(patsubst %.c,objs/gameplay/%.o,$(SRCS_GAMEPLAY))\
						$(patsubst %.c,objs/manager/%.o,$(SRCS_GESTION))\
						$(patsubst %.c,objs/calcul/%.o,$(SRCS_CALCUL))	\
						$(patsubst %.c,objs/editor/%.o,$(SRCS_EDITOR))	\
						$(patsubst %.c,objs/render/rasterisation/%.o,$(SRCS_RASTERIZE))\

SRCS_LIBFT		:=		$(patsubst %.c,libft/%.c,$(SRCS_LIBFT))
