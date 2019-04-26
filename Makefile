# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 18:09:49 by tbottini          #+#    #+#              #
#    Updated: 2019/04/26 15:57:26 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=		wolf3d

CC				:=		gcc

CFLAGS			:=		-g -Wall -Wextra -Werror

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

SRCS_LIB	:=		ft_atoi.c			ft_bzero.c 			ft_isalnum.c 	\
					ft_isalpha.c 		ft_isascii.c 		ft_isdigit.c 	\
					ft_islower.c		ft_isprime.c		ft_isprint.c 	\
					ft_isspace.c		ft_isupper.c		ft_itoa.c 		\
					ft_lstadd.c 		ft_lstdel.c 		ft_lstdelone.c 	\
					ft_lstiter.c 		ft_lstmap.c 		ft_lstnew.c 	\
					ft_memalloc.c		ft_memccpy.c 		ft_memchr.c 	\
					ft_memcmp.c 		ft_memcpy.c 		ft_memdel.c 	\
					ft_memmove.c 		ft_memset.c			ft_nodenew.c 	\
					ft_nodepushat.c 	ft_nodepushbegin.c	ft_nodeprint_int.c\
					ft_nodepushend.c	ft_nodeadd_int.c	ft_putchar.c	\
					ft_putchar_fd.c 	ft_putendl.c 		ft_putendl_fd.c \
					ft_putnbr.c 		ft_putnbr_fd.c 		ft_putstr.c 	\
					ft_putstr_fd.c 		ft_sqrt.c 			ft_strcat.c 	\
					ft_strchr.c 		ft_strclr.c 		ft_strcmp.c 	\
					ft_strcpy.c 		ft_strdel.c 		ft_strdup.c 	\
					ft_strequ.c 		ft_striter.c 		ft_striteri.c 	\
					ft_strjoin.c 		ft_strlcat.c 		ft_strlen.c 	\
					ft_strmap.c 		ft_strmapi.c 		ft_strncat.c 	\
					ft_strncmp.c 		ft_strncpy.c 		ft_strnequ.c 	\
					ft_strnew.c 		ft_strnew_set.c 	ft_strnjoin.c 	\
					ft_strnstr.c 		ft_strrchr.c 		ft_strrev.c 	\
					ft_strsplit.c 		ft_strsrchr.c 		ft_strstr.c 	\
					ft_strsub.c 		ft_strtrim.c 		ft_tolower.c 	\
					ft_toupper.c 		ft_2dchar_make.c 	ft_pow.c		\
					ft_2dchar_free.c 	ft_abs.c			ft_printf.c 	\
					ft_strjoin_free.c 	get_next_line.c		ft_htoi.c 		\
					ft_fabs.c 			ft_noderm.c 		ft_noderm_int.c \
					ft_nodesearch_int.c ft_2dchar_print.c\


OBJDIR			:=		objs

SRCDIR			:=		srcs

NB_SRCS			:=		$(shell ls srcs/ | wc -l)

NB_OBJS			=		$(shell ls objs/ | wc -l | sed -e 's/[^0-9]//g')

MAX_FILL		:=		$$(( $(NB_SRCS)))

FILL_BAR		=		$$(( $(NB_OBJS) * $(MAX_FILL) / $(NB_SRCS)))

INV_FILL_BAR	=		$$(( $(MAX_FILL) - $(FILL_BAR)))

OBJS    		:=		$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

SRCS	   		:=		$(patsubst %.c,srcs/%.c,$(SRCS))

OBJS_LIB		:=		$(patsubst %.c,libft/%.o,$(SRCS_LIB))

all				:		$(NAME)

$(OBJDIR)/%.o	:		$(SRCDIR)/%.c
	@printf '\rCompilation $(NAME)\n'
	@printf '[\e[94m%*s' $(FILL_BAR) | tr ' ' '#'
	@printf '%*s\e[0m] \e[94m $<\e[0m' $(INV_FILL_BAR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf '\033[M\033[A'

$(NAME)			:		$(OBJS) $(OBJS_LIB) include/wolf3d.h libft/libft.h
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

