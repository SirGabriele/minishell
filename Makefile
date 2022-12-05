NAME = minishell 

LIBFT = libft/libft.a

SRC = main.c					\
	prompt.c					\
	launch_program.c			\
	highlight_syntax_error.c

CHECK =	get_missing_user_input.c	\
	check_paired_characters.c		\
	ft_check_quotes.c				\
	ft_check_forbidden_characters.c	\
	ft_check_isolated_ampersands.c

PARSING =	binary_tree.c						\
			binary_tree_utils.c					\
			free.c								\
			ft_lst.c							\
			get_list_infos.c					\
			get_pipeline_infos.c				\
			get_tokens.c						\
			lexer.c								\
			parse_spaces.c						\
			parsing.c							\
			convert_var_with_dollar.c			\
			dollar_utils.c						\
			get_redirections.c					\
			get_redirections_list.c				\
			get_redirections_modes_and_files.c	\
			utils_token.c

UTILS =	what_is_index_in.c

SRCS = $(addprefix src/, $(SRC))			\
	$(addprefix src/parsing/, $(PARSING))	\
	$(addprefix src/check/, $(CHECK))		\
	$(addprefix src/utils/, $(UTILS))

CC = clang

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
