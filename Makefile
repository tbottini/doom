# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/04/22 18:27:41 by tbottini         ###   ########.fr        #
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

SRCS			:=		main.c			 						\
						sdl_manager.c							\
						wolf_parseur.c							\
						wolf_init.c								\
						init_btns.c								\
						raycasting.c							\
						color.c									\
						input_hook.c							\
						loop_hook.c								\
						event_handler.c							\
						sdl_quit.c								\
						button_drawer.c							\
						button_action.c							\
						num_tools.c								\
						image_tools.c							\
						draw_tools.c							\
						ray_vertical.c							\
						ray_horizontal.c						\

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

$(NAME)	: $(OBJS)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o $(NAME) $(OBJS)
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

