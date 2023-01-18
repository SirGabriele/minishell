NAME = minishell 

LIBFT = libft/libft.a

SRC = get_pwd_prompt_bonus.c		\
	highlight_syntax_error_bonus.c	\
	launch_program_bonus.c			\
	main_bonus.c					\
	prompt_bonus.c

SIGNALS = signals_bonus.c

CHECK = check_casual_syntax_error_bonus.c	\
	check_paired_characters_bonus.c			\
	check_syntax_and_or_bonus.c				\
	check_syntax_first_token_bonus.c		\
	check_syntax_par_bonus.c				\
	check_syntax_pipe_bonus.c				\
	ft_check_quotes_bonus.c					\
	ft_check_syntax_error_bonus.c			\
	get_missing_user_input_bonus.c	


PARSING = build_binary_tree_bonus.c		\
	del_parenthesis_if_needed_bonus.c	\
	fill_token_bonus.c					\
	get_first_half_bonus.c				\
	get_list_infos_bonus.c				\
	get_mode_and_file_bonus.c			\
	get_pipeline_infos_bonus.c			\
	get_redirections_infos_bonus.c		\
	get_redirections_list_bonus.c		\
	get_second_half_bonus.c				\
	left_branch_bonus.c					\
	lexer_bonus.c						\
	manage_modes_and_files_bonus.c		\
	parse_quotes_bonus.c				\
	right_branch_bonus.c				\
	split_list_bonus.c					\
	start_binary_tree_bonus.c	


DOLLAR_EXPAND = expand_var_with_dollar_bonus.c	\
	get_new_content_bonus.c						\
	join_and_manage_dollar_bonus.c

EXEC = execute_cmd_bonus.c			\
	expand_dollar_heredoc_bonus.c	\
	handle_all_redirs_bonus.c		\
	heredoc_requested_bonus.c		\
	initialize_children_bonus.c		\
	launch_builtin_bonus.c			\
	launch_exec_bonus.c				\
	operator_and_handling_bonus.c	\
	operator_or_handling_bonus.c	\
	start_recursive_bonus.c			\
	verify_cmd_path_bonus.c			\

LINKED_LIST = ft_lstnew_env_entry_bonus.c	\
	ft_lstnew_node_bonus.c					\
	ft_lstnew_token_bonus.c					\
	initialize_node_bonus.c					\
	lstnew_env_link_bonus.c

UTILS =	convert_env_arr_into_ll_bonus.c		\
	convert_env_ll_into_arr_bonus.c			\
	count_args_bonus.c						\
	count_dollars_to_replace_bonus.c		\
	count_nb_of_tokens_left_bonus.c			\
	count_nb_tokens_bonus.c					\
	examine_dollar_conditions_bonus.c		\
	get_index_delimiter_bonus.c				\
	get_key_to_expand_bonus.c				\
	get_key_value_bonus.c					\
	get_nb_dollars_bonus.c					\
	is_all_digit_bonus.c					\
	identify_splitting_operator_bonus.c		\
	is_dollar_inside_quotes_bonus.c			\
	is_exit_value_out_of_range_bonus.c		\
	is_it_a_closed_quote_bonus.c			\
	is_last_token_and_or_bonus.c			\
	is_operator_bonus.c						\
	is_token_in_parenthesis_bonus.c			\
	is_token_type_a_redir_bonus.c			\
	print_checking_error_msg_bonus.c		\
	print_content_pipe_bonus.c				\
	remove_empty_tokens_bonus.c				\
	set_dollar_underscore_bonus.c			\
	set_exit_code_bonus.c					\
	sort_env_ll_bonus.c						\
	token_content_length_bonus.c			\
	what_is_dollar_in_bonus.c				\
	what_is_index_in_bonus.c				\
	what_is_oper_in_bonus.c

BUILTINS = change_value_if_key_exists_bonus.c	\
		check_errors_env_format_bonus.c			\
		ft_cd_bonus.c							\
		ft_echo_bonus.c							\
		ft_env_bonus.c							\
		ft_exit_bonus.c							\
		ft_export_bonus.c						\
		ft_pwd_bonus.c							\
		ft_unset_bonus.c						\
		get_env_bonus.c							\
		set_values_export_bonus.c

FREE = free_1_bonus.c	\
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
