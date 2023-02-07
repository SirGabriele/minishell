# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrousse <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 13:41:05 by kbrousse          #+#    #+#              #
#    Updated: 2023/02/07 17:05:34 by kbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 

LIBFT = libft/libft.a

SRC = highlight_syntax_error.c	\
	launch_program.c			\
	main.c						\
	prompt.c

SRC_B =	highlight_syntax_error_bonus.c	\
	launch_program_bonus.c				\
	main_bonus.c						\
	prompt_bonus.c

SIGNALS = signals.c	\
	signals_fork.c

SIGNALS_B = signals_bonus.c	\
	signals_fork_bonus.c

CHECK =	check_syntax_first_token.c	\
	ft_check_quotes.c				\
	check_syntax_redir.c			\
	check_syntax_pipe.c

CHECK_B = check_syntax_and_or_bonus.c		\
	check_syntax_first_token_bonus.c		\
	check_syntax_par_bonus.c				\
	check_syntax_pipe_bonus.c				\
	ft_check_quotes_bonus.c					\
	check_syntax_redir_bonus.c

PARSING = build_binary_tree.c		\
		start_binary_tree.c			\
		get_mode_and_file.c			\
		get_second_half.c			\
		parse_quotes.c				\
		fill_token.c				\
		get_pipeline_infos.c		\
		get_first_half.c			\
		get_redirections_infos.c	\
		lexer.c						\
		split_list.c				\
		get_list_infos.c			\
		get_redirections_list.c		\
		manage_modes_and_files.c

PARSING_B = build_binary_tree_bonus.c	\
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
	start_binary_tree_bonus.c			\
	split_list_bonus.c

DOLLAR_EXPAND = expand_var_with_dollar.c	\
			join_and_manage_dollar.c		\
			get_new_content.c

DOLLAR_EXPAND_B = expand_var_with_dollar_bonus.c	\
	get_new_content_bonus.c							\
	join_and_manage_dollar_bonus.c

EXEC = execute_cmd.c				\
	heredoc_requested.c				\
	launch_exec.c					\
	start_recursive.c				\
	expand_dollar_heredoc.c			\
	initialize_children.c			\
	initialize_pipes.c				\
	verify_cmd_path.c				\
	handle_all_redirs.c				\
	launch_builtin.c				\
	redirect_infile_outfile.c


EXEC_B = execute_cmd_bonus.c		\
	expand_dollar_heredoc_bonus.c	\
	handle_all_redirs_bonus.c		\
	heredoc_requested_bonus.c		\
	initialize_children_bonus.c		\
	initialize_pipes_bonus.c		\
	launch_builtin_bonus.c			\
	launch_exec_bonus.c				\
	operator_and_handling_bonus.c	\
	operator_or_handling_bonus.c	\
	start_recursive_bonus.c			\
	verify_cmd_path_bonus.c			\
	redirect_infile_outfile_bonus.c

LINKED_LIST = ft_lstnew_env_entry.c	\
		ft_lstnew_node.c			\
		ft_lstnew_token.c			\
		initialize_node.c			\
		lstnew_env_link.c

LINKED_LIST_B = ft_lstnew_env_entry_bonus.c	\
	ft_lstnew_node_bonus.c					\
	ft_lstnew_token_bonus.c					\
	initialize_node_bonus.c					\
	lstnew_env_link_bonus.c

UTILS = convert_env_arr_into_ll.c	\
	convert_env_ll_into_arr.c		\
	count_args.c					\
	count_dollars_to_replace.c		\
	count_nb_of_tokens_left.c		\
	examine_dollar_conditions.c		\
	get_index_delimiter.c			\
	get_key_to_expand.c				\
	get_key_value.c					\
	get_nb_dollars.c				\
	is_all_digit.c					\
	is_dollar_inside_quotes.c		\
	is_exit_value_out_of_range.c	\
	is_it_a_closed_quote.c			\
	is_there_pipes.c				\
	is_token_type_a_redir.c			\
	print_checking_error_msg.c		\
	print_content_pipe.c			\
	remove_empty_tokens.c			\
	set_dollar_underscore.c			\
	set_exit_code.c					\
	should_expand_this_dollar.c		\
	sort_env_ll.c					\
	token_content_length.c			\
	what_is_dollar_in.c				\
	what_is_index_in.c

UTILS_B =	convert_env_arr_into_ll_bonus.c	\
	convert_env_ll_into_arr_bonus.c			\
	count_args_bonus.c						\
	count_dollars_to_replace_bonus.c		\
	count_nb_of_tokens_left_bonus.c			\
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
	is_operator_bonus.c						\
	is_token_in_parenthesis_bonus.c			\
	is_token_type_a_redir_bonus.c			\
	print_checking_error_msg_bonus.c		\
	print_content_pipe_bonus.c				\
	remove_empty_tokens_bonus.c				\
	set_dollar_underscore_bonus.c			\
	set_exit_code_bonus.c					\
	should_expand_this_dollar_bonus.c		\
	sort_env_ll_bonus.c						\
	token_content_length_bonus.c			\
	what_is_dollar_in_bonus.c				\
	what_is_index_in_bonus.c				\
	what_is_oper_in_bonus.c

BUILTINS = change_value_if_key_exists.c	\
	check_errors_env_format.c			\
	ft_echo.c							\
	ft_exit.c							\
	ft_export.c							\
	get_env.c							\
	ft_unset.c							\
	ft_env.c							\
	ft_pwd.c							\
	set_values_export.c					\
	ft_cd.c

BUILTINS_B = change_value_if_key_exists_bonus.c	\
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

FREE = free_1.c	\
	free_2.c

FREE_B = free_1_bonus.c	\
	free_2_bonus.c

SRCS = $(addprefix mandatory/src/, $(SRC))						\
	$(addprefix mandatory/src/signals/, $(SIGNALS))				\
	$(addprefix mandatory/src/check/, $(CHECK))					\
	$(addprefix mandatory/src/parsing/, $(PARSING))				\
	$(addprefix mandatory/src/exec/, $(EXEC))					\
	$(addprefix mandatory/src/linked_list/, $(LINKED_LIST))		\
	$(addprefix mandatory/src/utils/, $(UTILS))					\
	$(addprefix mandatory/src/dollar_expand/, $(DOLLAR_EXPAND))	\
	$(addprefix mandatory/src/builtins/, $(BUILTINS))			\
	$(addprefix mandatory/src/free/, $(FREE))

SRCS_B = $(addprefix bonus/src/, $(SRC_B))						\
	$(addprefix bonus/src/signals/, $(SIGNALS_B))				\
	$(addprefix bonus/src/check/, $(CHECK_B))					\
	$(addprefix bonus/src/parsing/, $(PARSING_B))				\
	$(addprefix bonus/src/exec/, $(EXEC_B))						\
	$(addprefix bonus/src/linked_list/, $(LINKED_LIST_B))		\
	$(addprefix bonus/src/utils/, $(UTILS_B))					\
	$(addprefix bonus/src/dollar_expand/, $(DOLLAR_EXPAND_B))	\
	$(addprefix bonus/src/builtins/, $(BUILTINS_B))				\
	$(addprefix bonus/src/free/, $(FREE_B))

CC = clang

FLAGS = -Wall -Wextra -Werror -g

READLINE = -lreadline

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

ifdef BONUS
	SRCS = $(SRCS_B)
endif

all: $(NAME)

clean:
	@rm -f $(OBJS_B) $(OBJS)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~     Clean terminated!     ~"
	@echo "*         mihishell         *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

fclean: clean
	@make fclean -C libft --no-print-directory
	@rm -f $(NAME)

re: fclean all

%.o: %.c
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) -Llibft -lft $(READLINE) -o $(NAME)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~  Compilation terminated!  ~"
	@echo "*         minishell         *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

bonus:
	@make BONUS=1 --no-print-directory

$(LIBFT):
	@make -C libft --no-print-directory

.PHONY: all clean fclean re bonus
