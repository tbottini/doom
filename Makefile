# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/05/03 12:15:50 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include libft/include.mk
include doom.mk

NAME			:=		doom-nukem

CC				:=		gcc

CFLAGS			:=		-Wall -Wextra\

LIB				:=		-L libft/ -lft							\
						-L ~/.brew/lib -lSDL2					\
						-lSDL2_ttf								\
						-lSDL2_image							\

INCLUDE			=		-I ./include							\
						-I ./libft								\
						-I ~/.brew/include/SDL2					\

FOLDER			:=		objs									\
						objs/parsing							\
						objs/render								\
						objs/debug

COMPILE_LIB		:=		make -C libft/

OBJDIR			:=		objs

SRCDIR			:=		srcs

NB_SRCS			:=		$(shell ls srcs/ | wc -l)

NB_OBJS			=		$(shell ls objs/ | wc -l | sed -e 's/[^0-9]//g')

MAX_FILL		:=		$$(( $(NB_SRCS)))

FILL_BAR		=		$$(( $(NB_OBJS) * $(MAX_FILL) / $(NB_SRCS)))

INV_FILL_BAR	=		$$(( $(MAX_FILL) - $(FILL_BAR)))


all				:		directory $(NAME)

directory		:
	@mkdir -p $(FOLDER)

$(OBJDIR)/%.o	:		$(SRCDIR)/%.c $(SRCS_LIBFT) include/doom.h libft/libft.h
	@printf '\rCompilation $(NAME)\n'
	@printf '[\e[94m%*s' $(FILL_BAR) | tr ' ' '#'
	@printf '%*s\e[0m] \e[94m $<\e[0m' $(INV_FILL_BAR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf '\033[M\033[A'

$(NAME)			:		$(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o main/main.o main/main.c
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o $(NAME) main/main.o $(OBJS)
	@sips -i ressources/icon/icon.ico
	@derez -only icns ressources/icon/icon.ico > tmpicns.rsrc
	@rez -append tmpicns.rsrc -o $(NAME)
	@setfile -a C $(NAME)
	@rm tmpicns.rsrc
	@printf "\e[M\e[A\n\e[94m[--------$(NAME)--------]\n\e[0m"

clean			:
	@make clean -C ./libft
	@rm -f $(OBJS)
	@rm -rf $(FOLDER)

fclean			: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

parsing			:		directory $(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o main/main_parsing.o main/main_parsing.c
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o parsing $(OBJS) main/main_parsing.o
	@printf "\e[M\e[A\n\e[93m[--------PARSING_TEST--------]\n\e[0m"

re				: fclean all

.PHONY: all clean fclean re
