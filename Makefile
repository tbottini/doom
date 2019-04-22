#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/04/21 13:22:37 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=		wolf3d

CC				:=		gcc

CFLAGS			:=		-g -Wall -Wextra \
						-I/Users/$(shell whoami)/.brew/include/SDL2\
						-Wconversion
#-Werror

FMLX		=	-L/Users/$(shell whoami)/.brew/lib -lSDL2 -lSDL2_ttf -lSDL2_image

LIB				:=		-L libft/ -lft							



INCLUDE			:=		-I ./include							\
						-I ./libft								\

SRCS			:=		srcs/main.c			 					\
						srcs/sdl_manager.c						\
						srcs/wolf_parseur.c						\
						srcs/wolf_init.c						\
						srcs/init_btns.c						\
						srcs/init_btns2.c						\
						srcs/raycasting.c						\
						srcs/color.c							\
						srcs/input_hook.c						\
						srcs/loop_hook.c						\
						srcs/event_handler.c					\
						srcs/sdl_quit.c							\
						srcs/button_drawer.c					\
						srcs/button_action.c					\
						srcs/button_loader.c					\
						srcs/num_tools.c					\

NB_SRCS			:=		$(shell ls srcs/*.c | wc -l)

NB_OBJS			=		$(shell ls srcs | rev | grep "^o" | wc -l | sed -e 's/[^0-9]//g')

MAX_FILL		:=		$$(( $(NB_SRCS)))

FILL_BAR		=		$$(( $(NB_OBJS) * $(MAX_FILL) / $(NB_SRCS)))

INV_FILL_BAR	=		$$(( $(MAX_FILL) - $(FILL_BAR)))

OBJS = $(SRCS:.c=.o)

all: $ $(NAME)

%.o		:		%.c
	@printf '\rCompilation Libft\n'
	@printf '[\e[94m%*s' $(FILL_BAR) | tr ' ' '#'
	@printf '%*s\e[0m] \e[94m $<\e[0m' $(INV_FILL_BAR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf '\033[M\033[A'

$(NAME)	: $(OBJS)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(FMLX) $(LIB) $(INCLUDE) -o $(NAME) $(OBJS)
	@printf "\e[M\e[A\n\e[94m[--------$(NAME)--------]\n"

clean:
	@make clean -C ./libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

start	:	all
	$(shell ./$(NAME))

re: fclean all

.PHONY: all clean fclean re a

