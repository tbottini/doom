SRCS_DOOM		:=		editor_finder.c									\
						editor_render.c									\
						editor_input.c									\
						editor_optionbox.c								\
						editor_txtrbox.c								\
						editor_hook.c									\
						editor_write.c									\
						button_function.c								\
						slider_function.c								\
						main.c											\
						savefile.c										\
						readfile.c										\
						readfileeditor.c								\
						checkfile.c										\
						cinematri.c										\

SRCS_UI			:=		button_action.c									\
						button_drawer.c									\
						button_hover.c									\
						button_loader.c									\
						init_btns_edit.c								\
						init_btns.c										\
						init_btns2.c									\
						init_btns3.c									\
						init_slids.c									\
						fire.c											\


SRCS_INPUT		:=		event_controller.c								\
						event_handler.c									\
						event_handler_doom.c							\
						event_handler_editor.c							\
						input_hook.c									\
						loop_hook.c										\
						action.c										\
						move.c											\
						shoot.c											\
						shoot_tools.c									\
						collision.c										\
						keyboard_input.c								\
						debug_input.c									\

SRCS_RENDER		:=		render.c										\
						bunch.c											\
						wall.c											\
						bresenham.c										\
						draw_line.c										\
						draw_text.c										\
						sector.c										\
						minimap.c										\
						minimap_drawer.c								\
						backface.c										\
						render_effect.c									\
						render_wall.c									\
						render_portal.c									\
						pillar_info.c									\
						textures.c										\
						shape.c											\
						draw_column.c									\
						borne.c											\

#SRCS_PARSING	:=		parsing.c										\
						chunck.c										\
						chunk_ressources.c								\
						line_wall.c

SRCS_DEBUG		:=		debug_sector.c									\
						debug_screen.c									\
						debug_vector.c									\

SRCS_TOOLS		:=		list_tools.c									\
						editor_tools.c									\
						entity_tools.c									\
						file_tools.c									\
						mur_tools.c										\
						little_tools.c									\
						num_tools.c										\
						sdl_tools.c										\
						secteur_tools.c									\
						musi.c											\

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
						arch_manager.c								\

SRCS_CALCUL		:=		affine.c										\
						extra_calcul.c									\

OBJS			:=		$(patsubst %.c,objs/%.o,$(SRCS_DOOM))			\
						$(patsubst %.c,objs/render/%.o,$(SRCS_RENDER))	\
						$(patsubst %.c,objs/parsing/%.o,$(SRCS_PARSING))\
						$(patsubst %.c,objs/debug/%.o,$(SRCS_DEBUG))	\
						$(patsubst %.c,objs/tools/%.o,$(SRCS_TOOLS))	\
						$(patsubst %.c,objs/ui/%.o,$(SRCS_UI))			\
						$(patsubst %.c,objs/input/%.o,$(SRCS_INPUT))	\
						$(patsubst %.c,objs/manager/%.o,$(SRCS_GESTION))\
						$(patsubst %.c,objs/calcul/%.o,$(SRCS_CALCUL))

SRCS_LIBFT		:=		$(patsubst %.c,libft/%.c,$(SRCS_LIBFT))
