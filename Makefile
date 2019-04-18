#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/04/18 17:22:45 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=		wolf3d

CC				:=		gcc

CFLAGS			:=		-Wall -Wextra \
						-I/Users/$(shell whoami)/.brew/include/SDL2
#-Werror

FMLX		=	-L/Users/$(shell whoami)/.brew/lib -lSDL2 -lSDL2_ttf

LIB				:=		-L libft/ -lft							



INCLUDE			:=		-I ./include							\
						-I ./libft								\

SRCS			:=		srcs/wolf3d.c		 					\
						srcs/sdl_manager.c						\
						srcs/wolf_parseur.c						\
						srcs/init_btns.c						\
						srcs/raycasting.c						\
						srcs/color.c							\
						srcs/input_hook.c						\
						srcs/event_handler.c					\
						srcs/sdl_quit.c							\

NB_SRCS			:=		$(shell ls srcs/*.c | wc -l)

NB_OBJS			=		$(shell ls srcs | rev | grep "^o" | wc -l | sed -e 's/[^0-9]//g')

MAX_FILL		:=		$$(( $(NB_SRCS)))

FILL_BAR		=		$$(( $(NB_OBJS) * $(MAX_FILL) / $(NB_SRCS)))

INV_FILL_BAR	=		$$(( $(MAX_FILL) - $(FILL_BAR)))

OBJS = $(SRCS:.c=.o)

all: $ $(NAME)

%.o		:		%.c
	@printf '\rCompilation Libft\n'
	@printf '[\e[31m%*s' $(FILL_BAR) | tr ' ' '#'
	@printf '%*s\e[0m] \e[31m $<\e[0m' $(INV_FILL_BAR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf '\033[M\033[A'

$(NAME)	: $(OBJS)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(FMLX) $(LIB) $(INCLUDE) -o $(NAME) $(OBJS)
	@printf "\e[M\e[A\n\e[31m[--------$(NAME)--------]\n"

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

