NAME = minishell 

LIBFT = libft/libft.a

SRC = main.c					\
	prompt.c					\
	launch_program.c			\
	highlight_syntax_error.c

SIGNALS = signals_one.c

CHECK =	get_missing_user_input.c	\
	check_paired_characters.c		\
	ft_check_quotes.c				\
	ft_check_forbidden_characters.c

PARSING =   start_binary_tree.c	\
	fill_token.c				\
	get_list_infos.c			\
	get_pipeline_infos.c		\
	lexer.c						\
	parse_quotes.c				\
	expand_var_with_dollar.c	\
	manage_dollar.c				\
	get_redirections_list.c		\
	get_redirections_infos.c	\
	manage_modes_and_files.c	\
	get_mode_and_file.c			\
	identify_delim_token.c		\
	split_list.c				\
	get_first_half.c			\
	get_second_half.c			\
	left_branch.c				\
	right_branch.c


EXEC =	print_structs.c		\
	initialize_children.c	\
	start_recursive.c		\
	launch_exec.c			\
	handle_all_redirs.c		\
	heredoc_requested.c		\
	execute_cmd.c			\
	verify_cmd_path.c

LINKED_LIST = ft_lstnew_env_entry.c	\
	initialize_node.c				\
	ft_lstnew_token.c				\
	ft_lstnew_node.c

UTILS =	what_is_index_in.c		\
	convert_env_arr_into_ll.c	\
	convert_env_ll_into_arr.c	\
	binary_tree_utils.c			\
	dollar_utils.c				\
	utils_token.c

FREE = free.c	\
	free_2.c

SRCS = $(addprefix src/, $(SRC))					\
	$(addprefix src/signals/, $(SIGNALS))			\
	$(addprefix src/check/, $(CHECK))				\
	$(addprefix src/parsing/, $(PARSING))			\
	$(addprefix src/exec/, $(EXEC))					\
	$(addprefix src/linked_list/, $(LINKED_LIST))	\
	$(addprefix src/utils/, $(UTILS))				\
	$(addprefix src/free/, $(FREE))

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
