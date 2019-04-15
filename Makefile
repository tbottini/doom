#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/04/15 18:16:57 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=		Wolf3d

CC				:=		gcc

CFLAGS			:=		-Wall -Wextra -Werror

LIB				:=		-L libft/ -lft							\
						-L sdl2/2.0.9/lib -lSDL2				\
						-L sdl2_image/2.0.4/lib/ -lSDL2_image	\


INCLUDE			:=		-I ./include							\
						-I ./libft								\
						-I ./sdl2/2.0.9/include					\
						-I ./sdl2_image/2.0.4/include			\

SRCS			:=		srcs/wolf3d.c		 					\
						srcs/sdl_manager.c						\
						srcs/wolf_parseur.c						\
						srcs/raycasting.c						\

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
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o $(NAME) $(OBJS)
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

