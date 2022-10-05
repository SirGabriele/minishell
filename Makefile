# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 10:12:21 by kbrousse          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/10/04 09:25:39 by kbrousse         ###   ########.fr        #
=======
#    Updated: 2022/10/04 10:23:50 by jsauvain         ###   ########.fr        #
>>>>>>> d85fc3372b4bc30914889298d15029288add55b5
#                                                                              #
# **************************************************************************** #

NAME = minishell 

<<<<<<< HEAD
LIBFT = libft/libft.a

SRC = main.c	\
	echo.c
=======
SRC = main.c builtins.c parsing.c prompt.c
>>>>>>> d85fc3372b4bc30914889298d15029288add55b5

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
<<<<<<< HEAD
	@make fclean -C libft --no-print-directory
=======
	@make fclean -sC libft
>>>>>>> d85fc3372b4bc30914889298d15029288add55b5
	@rm -f $(NAME)

re: fclean all

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $<
 
<<<<<<< HEAD
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(READLINE) -Llibft -lft -Ilibft -o $(NAME)
=======
$(NAME): $(OBJS)
	@make -sC libft
	@$(CC) $(FLAGS) -L. $(OBJS) -Llibft -lft $(READLINE) -o $(NAME)
>>>>>>> d85fc3372b4bc30914889298d15029288add55b5
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~  Compilation terminated!  ~"
	@echo "*         minishell         *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

$(LIBFT):
	@make -C libft --no-print-directory

.PHONY: all clean fclean re
