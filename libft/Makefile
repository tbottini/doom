# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/15 19:18:49 by magrab            #+#    #+#              #
#    Updated: 2019/04/28 16:40:42 by tbottini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include include.mk

NAME		:=		libft.a

INCLUDE 	:=		-I /usr/local/include -I ../include

CC			:=		gcc

CFLAGS		:=		-Wall -Wextra -Werror

LIB 		:=

NB_SRCS			:=		$(shell ls *.c | wc -l)

NB_OBJS			=		$(shell ls | rev | grep "^o" | wc -l | sed -e 's/[^0-9]//g')

MAX_FILL		:=		$$(( $(NB_SRCS) / 2))

FILL_BAR		=		$$(( $(NB_OBJS) * $(MAX_FILL) / $(NB_SRCS)))

PERCENT			=		$$((  $(NB_OBJS) * 100 / $(NB_SRCS)))

INV_FILL_BAR	=		$$(( $(MAX_FILL) - $(FILL_BAR)))

OBJS = $(SRCS_LIBFT:.c=.o)

all: $ $(NAME)

%.o		:		%.c libft.h
	@printf '\rCompilation $(NAME)\n'
	@printf '[\e[36m%*s' $(FILL_BAR) | tr ' ' '#'
	@printf '%*s\e[0m] \e[36m $<\e[0m' $(INV_FILL_BAR)
	@$(CC) $(CFLAGS)  -c -o $@ $<
	@printf '\033[M\033[A'

$(NAME)	: $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "\e[M\e[A\n\e[36m[--------Libft--------]\n\e[0m"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

verif		:
	norminette $(SRCS_LIBFT) include/libft.h
	$(all)

re: fclean all

.PHONY: all clean fclean re a
