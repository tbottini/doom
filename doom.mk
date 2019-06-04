SRCS_DOOM		:=		editor.c										\
						editor_hook.c									\
						button_function.c								\
						slider_function.c								\
						main.c

SRCS_UI			:=		button_action.c									\
						button_drawer.c									\
						button_hover.c									\
						button_loader.c									\
						init_btns.c										\
						init_btns2.c									\
						init_slids.c									\
						fire.c											\


SRCS_INPUT		:=		event_controller.c								\
						event_handler.c									\
						event_handler1.c								\
						event_handler2.c								\
						input_hook.c									\
						loop_hook.c										\
						action.c										\
						move.c											\
						shoot.c											\
						collision.c										\
						keyboard_input.c

SRCS_RENDER		:=		render.c										\
						bunch.c											\
						wall.c											\
						bresenham.c										\
						draw_wall.c										\
						draw_line.c										\
						draw_text.c										\
						sector.c										\
						minimap.c										\
						backface.c

SRCS_PARSING	:=		parsing.c										\
						chunck.c

SRCS_DEBUG		:=		debug_sector.c									\
						debug_screen.c									\
						debug_vector.c

SRCS_TOOLS		:=		num_tools.c										\
						little_tools.c									\
						list_tools.c									\
						sdl_tools.c

SRCS_GESTION	:=		doom_manager.c									\
						sdl_manager.c									\
						ui_manager.c									\
						player_manager.c								\
						editor_manager.c								\
						designer_manager.c

OBJS			:=		$(patsubst %.c,objs/%.o,$(SRCS_DOOM))			\
						$(patsubst %.c,objs/render/%.o,$(SRCS_RENDER))	\
						$(patsubst %.c,objs/parsing/%.o,$(SRCS_PARSING))\
						$(patsubst %.c,objs/debug/%.o,$(SRCS_DEBUG))	\
						$(patsubst %.c,objs/tools/%.o,$(SRCS_TOOLS))	\
						$(patsubst %.c,objs/ui/%.o,$(SRCS_UI))			\
						$(patsubst %.c,objs/input/%.o,$(SRCS_INPUT))	\
						$(patsubst %.c,objs/manager/%.o,$(SRCS_GESTION))

SRCS_LIBFT		:=		$(patsubst %.c,libft/%.c,$(SRCS_LIBFT))
