NAME = minishell 

LIBFT = libft/libft.a

SRC = main_bonus.c					\
	prompt_bonus.c					\
	launch_program_bonus.c			\
	highlight_syntax_error_bonus.c	\
	get_pwd_prompt_bonus.c

SIGNALS = signals_one_bonus.c

CHECK =	get_missing_user_input_bonus.c	\
	check_paired_characters_bonus.c		\
	ft_check_syntax_error.c				\
	ft_check_quotes_bonus.c

PARSING =   start_binary_tree_bonus.c	\
	build_binary_tree_bonus.c			\
	del_parenthesis_if_needed_bonus.c	\
	fill_token_bonus.c					\
	get_list_infos_bonus.c				\
	get_pipeline_infos_bonus.c			\
	lexer_bonus.c						\
	parse_quotes_bonus.c				\
	get_redirections_list_bonus.c		\
	get_redirections_infos_bonus.c		\
	manage_modes_and_files_bonus.c		\
	get_mode_and_file_bonus.c			\
	split_list_bonus.c					\
	get_first_half_bonus.c				\
	get_second_half_bonus.c				\
	left_branch_bonus.c					\
	right_branch_bonus.c

DOLLAR_EXPAND = expand_var_with_dollar_bonus.c	\
			get_new_content_bonus.c				\
			join_and_manage_dollar_bonus.c

EXEC = initialize_children_bonus.c	\
	start_recursive_bonus.c			\
	launch_exec_bonus.c				\
	handle_all_redirs_bonus.c		\
	heredoc_requested_bonus.c		\
	execute_cmd_bonus.c				\
	verify_cmd_path_bonus.c			\
	operator_and_handling_bonus.c	\
	launch_builtin_bonus.c			\
	operator_or_handling_bonus.c	\
	expand_dollar_heredoc_bonus.c

LINKED_LIST = ft_lstnew_env_entry_bonus.c	\
	initialize_node_bonus.c					\
	ft_lstnew_token_bonus.c					\
	ft_lstnew_node_bonus.c

UTILS =	what_is_index_in_bonus.c	\
	convert_env_arr_into_ll_bonus.c	\
	convert_env_ll_into_arr_bonus.c	\
	utils_binary_tree_bonus.c		\
	utils_dollar_1_bonus.c			\
	utils_dollar_2_bonus.c			\
	utils_tokens_1_bonus.c			\
	utils_tokens_2_bonus.c			\
	utils_exit_code_bonus.c			\
	print_content_pipe_bonus.c		\
	utils_check_syntax.c

BUILTINS = ft_echo_bonus.c					\
		ft_cd_bonus.c						\
		ft_pwd_bonus.c						\
		ft_export_bonus.c					\
		ft_unset_bonus.c					\
		ft_env_bonus.c						\
		change_value_if_key_exists_bonus.c	\
		check_errors_env_format_bonus.c		\
		extend_env_list_bonus.c				\
		get_env_bonus.c						\
		set_values_export_bonus.c

FREE = free_bonus.c	\
	free_2_bonus.c

SRCS = $(addprefix src/, $(SRC))						\
	$(addprefix src/signals/, $(SIGNALS))				\
	$(addprefix src/check/, $(CHECK))					\
	$(addprefix src/parsing/, $(PARSING))				\
	$(addprefix src/exec/, $(EXEC))						\
	$(addprefix src/linked_list/, $(LINKED_LIST))		\
	$(addprefix src/utils/, $(UTILS))					\
	$(addprefix src/dollar_expand/, $(DOLLAR_EXPAND))	\
	$(addprefix src/builtins/, $(BUILTINS))				\
	$(addprefix src/free/, $(FREE))

CC = clang

FLAGS = -Wall -Wextra -Werror -gdwarf-4

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
