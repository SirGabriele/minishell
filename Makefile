# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 10:12:21 by kbrousse          #+#    #+#              #
#    Updated: 2022/10/03 09:48:19 by jsauvain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 

SRC = main.c builtins.c

SRCS = $(addprefix src/, $(SRC))

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

READLINE = -lreadline

OBJS = $(SRCS:.c=.o)

all: $(NAME)

clean:
	@make clean -sC libft
	@rm -f $(OBJS)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~     Clean terminated!     ~"
	@echo "*         mihishell         *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

fclean: clean
	@make fclean -sC libft
	@rm -f $(NAME)

re: fclean all

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $<
 
$(NAME): $(OBJS)
	@make -sC libft
	@$(CC) $(FLAGS) -L. $(OBJS) -Llibft -lft $(READLINE) -o $(NAME)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~  Compilation terminated!  ~"
	@echo "*         minishell         *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

.PHONY: all clean fclean re
