# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akrache <akrache@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/07/29 11:57:24 by akrache          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include libft/include.mk
include doom.mk

NAME			:=		doom-nukem

CC				:=		gcc

CFLAGS			:=		-Wall -Wextra -g #-fsanitize=address#-Werror -Ofast -fno-builtin -flto

LIB				:=		-L libft/ -lft							\
						-L ~/.brew/lib -lSDL2					\
						-lSDL2_ttf								\
						-lSDL2_image							\
						-lSDL2_mixer							\

INCLUDE			:=		-I ./include							\
						-I ./libft								\
						-I ~/.brew/include/SDL2					\

HEADERS			:=		libft/libft.h							\
						include/doom_nukem.h					\
						include/calcul.h						\
						include/debug.h							\
						include/doom_struct.h					\
						include/editor.h						\
						include/vector.h						\
						include/render.h						\
						include/player.h						\
						include/input.h							\
						include/sector.h						\


FOLDER			:=		objs									\
						objs/render								\
						objs/parsing							\
						objs/debug								\
						objs/tools								\
						objs/ui									\
						objs/input								\
						objs/gameplay							\
						objs/manager							\
						objs/calcul								\
						objs/editor								\
						objs/render/hud							\
						objs/render/pre_render					\
						objs/render/drawer						\

COMPILE_LIB		:=		make -C libft/

OBJDIR			:=		objs

SRCDIR			:=		srcs

NB_SRCS			:=		$(shell find srcs/ -type f | wc -l)

NB_OBJS			=		$(shell find objs/ -type f | wc -l | sed -e 's/[^0-9]//g')

MAX_FILL		:=		$$(( $(NB_SRCS) ))

FILL_BAR		=		$$(( $(NB_OBJS) + 1 * $(MAX_FILL) / $(NB_SRCS)))

INV_FILL_BAR	=		$$(( $(MAX_FILL) - $(FILL_BAR)))

all				:		$(FOLDER) $(NAME)

$(FOLDER)		:
	@mkdir -p $(FOLDER)

$(OBJDIR)/%.o	:		$(SRCDIR)/%.c $(HEADERS)
	@printf '\rCompilation $(NAME)\n' \
	&& printf '[\e[94m%*s' $(FILL_BAR) | tr ' ' '#' \
	&& printf '%*s\e[0m] \e[94m $<\e[0m\n' $(INV_FILL_BAR) \
	&& $(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $< \
	&& printf '\033[A\033[M\033[A'

$(NAME)			:		$(OBJS) $(SRCS_LIBFT)
	@make -C libft/
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o $(NAME) $(OBJS)
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

lclean			:
	@rm -rf $(FOLDER)

chmain			:
	@mv srcs/main.c main/main2.c
	@mv main/main.c srcs/main.c
	@mv main/main2.c main/main.c
	@touch srcs/main.c
	@make

start			:	all
	./doom-nukem $(ARGS)

re				:	fclean all

.PHONY: all clean fclean re
