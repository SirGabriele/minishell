NAME = minishell 

LIBFT = libft/libft.a

SRC = main.c					\
	builtins.c					\
	prompt.c					\
	launch_program.c			\
	highlight_syntax_error.c

INIT = init_struct_array.c

CHECK = ft_check_quotes.c		\
	ft_check_ampersands.c		\
	ft_check_shifts.c			\
	ft_check_pipes.c			\
	get_missing_user_input.c

PARSING =	convert_var_with_dollar.c	\
	utils_filter.c

SRCS = $(addprefix src/, $(SRC))			\
	$(addprefix src/parsing/, $(PARSING))	\
	$(addprefix src/init/, $(INIT))			\
	$(addprefix src/check/, $(CHECK))

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

READLINE = -lreadline

OBJS = $(SRCS:.c=.o)

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~     Clean terminated!     ~"
	@echo "*         mihishell         *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

fclean: clean
	@make fclean -C libft --no-print-directory
	@rm -f $(NAME)

re: fclean all

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -Llibft -lft -Ilibft $(READLINE) -o $(NAME)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~  Compilation terminated!  ~"
	@echo "*         minishell         *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

$(LIBFT):
	@make -C libft --no-print-directory

.PHONY: all clean fclean re
