# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/05/09 13:33:03 by tbottini         ###   ########.fr        #
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

INCLUDE			:=		-I ./include							\
						-I ./libft								\
						-I ~/.brew/include/SDL2					\

INCLUDE_RES		:=		include/sector.h						\
						include/vector.h						\
						libft/libft.h							\
						include/doom_nukem.h

FOLDER			:=		objs									\
						objs/parsing							\
						objs/render								\
						objs/debug								\
						objs/tools								\
						objs/ui									\
						objs/input								\
						objs/manager

COMPILE_LIB		:=		make -C libft/

OBJDIR			:=		objs

SRCDIR			:=		srcs

NB_SRCS			:=		$(shell find srcs/ -type f | wc -l)

NB_OBJS			=		$(shell find objs/ -type f | wc -l | sed -e 's/[^0-9]//g')

MAX_FILL		:=		$$(( $(NB_SRCS) ))

FILL_BAR		=		$$(( $(NB_OBJS) + 1 * $(MAX_FILL) / $(NB_SRCS)))

INV_FILL_BAR	=		$$(( $(MAX_FILL) - $(FILL_BAR)))


all				:		directory $(NAME)

directory		:
	@mkdir -p $(FOLDER)

$(OBJDIR)/%.o	:		$(SRCDIR)/%.c $(SRCS_LIBFT) $(INCLUDE_RES)
	@printf '\rCompilation $(NAME)\n'
	@printf '[\e[94m%*s' $(FILL_BAR) | tr ' ' '#'
	@printf '%*s\e[0m] \e[94m $<\e[0m' $(INV_FILL_BAR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf '\033[M\033[A'

$(NAME)			:		$(OBJS)
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

parsing			:
	$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o parsing \
		srcs/parsing/*.c main_parsing.c srcs/tools/*.c srcs/debug/*.c

re				: fclean all

.PHONY: all clean fclean re
