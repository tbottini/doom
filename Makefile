# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/04/25 20:58:52 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=		wolf3d

CC				:=		gcc

CFLAGS			:=		-g -Wall -Wextra \
#-Werror

LIB				:=		-L libft/ -lft							\
						-L ~/.brew/lib -lSDL2					\
						-lSDL2_ttf								\
						-lSDL2_image							\

INCLUDE			=		-I ./include							\
						-I ./libft								\
						-I ~/.brew/include/SDL2					\

SRCS			:=		button_action.c							\
						button_drawer.c							\
						button_loader.c							\
						color.c									\
						draw_tools.c							\
						event_handler.c							\
						init_btns.c								\
						init_btns2.c							\
						init_slids.c							\
						input_hook.c							\
						loop_hook.c								\
						main.c			 						\
						num_tools.c								\
						ray_horizontal.c						\
						ray_vertical.c							\
						raycasting.c							\
						sdl_manager.c							\
						sdl_quit.c								\
						wolf_init.c								\
						wolf_parseur.c							\

OBJDIR			:=		objs

SRCDIR			:=		srcs

NB_SRCS			:=		$(shell ls srcs/ | wc -l)

NB_OBJS			=		$(shell ls objs/ | wc -l | sed -e 's/[^0-9]//g')

MAX_FILL		:=		$$(( $(NB_SRCS)))

FILL_BAR		=		$$(( $(NB_OBJS) * $(MAX_FILL) / $(NB_SRCS)))

INV_FILL_BAR	=		$$(( $(MAX_FILL) - $(FILL_BAR)))

OBJS    		:=		$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

SRCS	   		:=		$(patsubst %.c,srcs/%.c,$(SRCS))

all: $(NAME)

$(OBJDIR)/%.o		:		$(SRCDIR)/%.c
	@printf '\rCompilation $(NAME)\n'
	@printf '[\e[94m%*s' $(FILL_BAR) | tr ' ' '#'
	@printf '%*s\e[0m] \e[94m $<\e[0m' $(INV_FILL_BAR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf '\033[M\033[A'

$(NAME)	: $(OBJS) include/wolf3d.h libft/libft.h
	@make -C ./libft
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o $(NAME) $(OBJS)
	@sips -i ressources/icon/icon.ico
	@derez -only icns ressources/icon/icon.ico > tmpicns.rsrc
	@rez -append tmpicns.rsrc -o $(NAME)
	@setfile -a C $(NAME)
	@rm tmpicns.rsrc
	@printf "\e[M\e[A\n\e[94m[--------$(NAME)--------]\n\e[0m"

clean:
	@make clean -C ./libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

start	:	all
	$(shell ./$(NAME))

re: fclean all

.PHONY: all clean fclean re

