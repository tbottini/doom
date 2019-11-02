# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/08/26 16:12:04 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include libft/include.mk
include doom.mk

NAME			:=		doom-nukem

CC				:=		gcc

CFLAGS			:=		-Wall -Wextra -Werror -g -Ofast -fno-builtin -flto

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
						include/editor.h						\
						include/vector.h						\
						include/render.h						\
						include/player.h						\
						include/input.h							\
						include/sector.h						\
						include/screen.h						\
						include/architect.h						\

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
						objs/render/rasterisation				\

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
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(NAME)			:		$(OBJS) $(SRCS_LIBFT)
	@make -C libft/
	@$(CC) $(CFLAGS) $(LIB) $(INCLUDE) -o $(NAME) $(OBJS)
	@sips -i ressources/icon/icon.ico
	@derez -only icns ressources/icon/icon.ico > tmpicns.rsrc
	@rez -append tmpicns.rsrc -o $(NAME)
	@setfile -a C $(NAME)
	@rm tmpicns.rsrc

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

DOT_FILE		=		$(wildcard latex/*.dot)

PNG_FILE		= 		$(DOT_FILE:.dot=.png)

DOT_PATH		:=		latex

DOC_PATH		:=		html

$(DOT_PATH)/%.png:$(DOC_PATH)/%.dot
	@echo $@
	@dot -Tpng $< -o $@

convert_dot : $(PNG_FILE)

install_doc:
	brew install doxygen

doc		:
	doxygen -g
	sed -ie "s/HAVE_DOT               = NO/HAVE_DOT               = YES/g" Doxyfile
	sed -ie "s/EXTRACT_ALL            = NO/EXTRACT_ALL            = YES/g" Doxyfile
	sed -ie "s/EXTRACT_PRIVATE        = NO/EXTRACT_PRIVATE        = YES/g" Doxyfile
	sed -ie "s/EXTRACT_STATIC         = NO/EXTRACT_STATIC         = YES/g" Doxyfile
	sed -ie "s/CALL_GRAPH             = NO/CALL_GRAPH             = YES/g" Doxyfile
	sed -ie "s/RECURSIVE              = NO/RECURSIVE              = YES/g" Doxyfile
	sed -ie "s/DOT_CLEANUP            = YES/DOT_CLEANUP            = NO/g" Doxyfile
	doxygen Doxyfile
	@#$(eval DOT_FILE = $(wildcard latex/*.dot))
	@#$(eval PNG_FILE = $(DOT_FILE:.dot=.png))
	@#make convert_dot
	@#mv $(PNG_FILE) html/
	rm -f Doxyfilee
	rm -f Doxyfile.bak
	open html/index.html


doclean:
	rm -rf html latex Doxyfile
