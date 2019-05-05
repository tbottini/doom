SRCS_DOOM		:=		editor.c										\
						movement.c		 								\
						sdl_manager.c									\
						sdl_quit.c										\
						doom_init.c										\
						main.c

SRCS_UI			:=		button_action.c									\
						button_drawer.c									\
						button_hover.c									\
						button_loader.c									\
						init_btns.c										\
						init_btns2.c									\
						init_slids.c									\


SRCS_INPUT		:=		event_controller.c								\
						event_handler.c									\
						event_handler1.c								\
						event_handler2.c								\
						input_hook.c									\
						loop_hook.c										\
						keyboard_input.c

SRCS_RENDER		:=		bunch.c											\
						wall.c

SRCS_PARSING	:=		parsing.c

SRCS_DEBUG		:=		debug_sector.c

SRCS_TOOLS		:=		num_tools.c										\
						little_tools.c

SRCS_GESTION	:=		doom_gestion.c									\
						sdl_gestion.c									\
						ui_gestion.c									\
						editor_gestion.c

OBJS			:=		$(patsubst %.c,objs/%.o,$(SRCS_DOOM))			\
						$(patsubst %.c,objs/render/%.o,$(SRCS_RENDER))	\
						$(patsubst %.c,objs/parsing/%.o,$(SRCS_PARSING))\
						$(patsubst %.c,objs/debug/%.o,$(SRCS_DEBUG))	\
						$(patsubst %.c,objs/tools/%.o,$(SRCS_TOOLS))	\
						$(patsubst %.c,objs/ui/%.o,$(SRCS_UI))			\
						$(patsubst %.c,objs/input/%.o,$(SRCS_INPUT))	\
						$(patsubst %.c,objs/gestion/%.o,$(SRCS_GESTION))

SRCS_LIBFT		:=		$(patsubst %.c,libft/%.c,$(SRCS_LIBFT))
