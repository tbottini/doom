SRCS_WOLF		:=		button_action.c							\
						button_drawer.c							\
						button_hover.c							\
						button_loader.c							\
						little_tools.c							\
						draw_tools.c							\
						editor.c								\
						event_controller.c						\
						event_handler.c							\
						event_handler1.c						\
						event_handler2.c						\
						init_btns.c								\
						init_btns2.c							\
						init_slids.c							\
						input_hook.c							\
						loop_hook.c								\
						main.c			 						\
						movement.c		 						\
						num_tools.c								\
						sdl_manager.c							\
						sdl_quit.c								\
						doom_init.c								\
						main.c

SRCS_RENDER		:=		render.c								\
						wall.c

SRCS_PARSING	:=		parsing.c

SRCS_DEBUG		:=		debug_sector.c

OBJS			:=		$(patsubst %.c,objs/%.o,$(SRCS_WOLF))			\
						$(patsubst %.c,objs/render/%.o,$(SRCS_RENDER))	\
						$(patsubst %.c,objs/parsing/%.o,$(SRCS_PARSING))\
						$(patsubst %.c,objs/debug/%.o,$(SRCS_DEBUG))

SRCS_LIBFT		:=		$(patsubst %.c,libft/%.c,$(SRCS_LIBFT))
