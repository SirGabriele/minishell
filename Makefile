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

FREE =	free.c	\
		free_2.c

SIGNALS = signal.c

UTILS = binary_tree_utils.c	\
		dollar_utils.c		\
		utils_token.c

LINK_LIST = lstnew_token.c

PARSING =	binary_tree.c						\
			fill_token.c						\
			get_list_infos.c					\
			get_pipeline_infos.c				\
			lexer.c								\
			parse_quotes.c						\
			expand_var_with_dollar.c			\
			extract_env_variable_line.c			\
			manage_dollar.c						\
			get_redirections.c					\
			get_redirections_list.c				\
			manage_modes_and_files.c			\
			get_mode_and_file.c					\
			identify_delim_token.c				\
			split_list.c						\
			get_first_half.c					\
			get_second_half.c					\
			left_branch.c						\
			right_branch.c						\
			what_is_index_in.c

BUILTINS = ft_echo.c			\
			ft_cd.c				\
			ft_pwd.c			\
			ft_env.c			\
			ft_export.c			\
			set_values_export.c

SRCS = $(addprefix src/, $(SRC))				\
	$(addprefix src/parsing/, $(PARSING))		\
	$(addprefix src/check/, $(CHECK))			\
	$(addprefix src/free/, $(FREE))				\
	$(addprefix src/signals/, $(SIGNALS))		\
	$(addprefix src/link_list/, $(LINK_LIST))	\
	$(addprefix src/utils/, $(UTILS))			\
	$(addprefix src/builtins/, $(BUILTINS))

CC = clang

FLAGS = -Wall -Wextra -Werror -g3

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
