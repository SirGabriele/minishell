/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:52:12 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/20 01:29:51 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "structs_ms_bonus.h"
# include "../../libft/libft.h"

/*	signal()	*/
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

/*	open()	*/
# include <fcntl.h>

/********/
/*	SRC	*/
/********/

int				cmd_prompt(t_env_ms *env_ll);
int				launch_program(char *user_input, t_env_ms *env);
void			highlight_syntax_error(const char *str, int start, int end);

/************/
/*	CHECK	*/
/************/

int				check_syntax_first_token(t_token_ms *tokens, t_env_ms *env_ll);
int				check_syntax_redir(t_token_ms *tokens, t_env_ms *env_ll);
int				check_syntax_pipe(t_token_ms *tokens, t_env_ms *env_ll);
int				check_syntax_and_or(t_token_ms *tokens, t_env_ms *env_ll);
int				ft_check_isolated_quotes(const char *user_input, \
					t_env_ms *env_ll);

/************/
/*	SIGNALS	*/
/************/

void			set_signals_first_readline(void);
void			handler_heredoc(int sig);
void			handler_before_fork(void);
void			set_sigint_sigquit_to_default(void);

/************/
/*	EXEC	*/
/************/

int				launch_exec(t_node_ms *root, t_env_ms *env_ll);
t_children_ms	*initialize_children(int nb_nodes);
t_pipes_ms		*initialize_pipes(t_node_ms *root, t_children_ms *children);
t_node_ms		*apply_and_operator(t_pipes_ms *pipes, t_children_ms *children, \
					t_node_ms *node, t_env_ms *env_ll);
t_node_ms		*apply_or_operator(t_pipes_ms *pipes, t_children_ms *children, \
					t_node_ms *node, t_env_ms *env_ll);
char			*verify_cmd_path(char *user_input_cmd, char **env);
int				start_recursive(t_pipes_ms *pipes, t_children_ms *children, \
					t_node_ms *root, t_env_ms *env_ll);
int				handle_all_redirs(t_node_ms *node, t_pipes_ms *pipes, \
					t_env_ms *env_ll);
int				start_recursive(t_pipes_ms *pipes, t_children_ms *children, \
					t_node_ms *root, t_env_ms *env);
int				heredoc_requested(t_redir_ms *redir, t_pipes_ms *pipes, \
					t_env_ms *env_ll);
int				execute_cmd(t_pipes_ms *pipes, t_children_ms *children, \
					t_node_ms *node, \
					t_env_ms **env);
int				is_a_builtin(char *content);
int				exec_builtin(t_node_ms *node, t_env_ms **env_ll,
					t_pipes_ms *pipes, int exit_code_redirs);
void			expand_dollar_heredoc(char *user_input, t_pipes_ms *pipes, \
					t_env_ms *env_ll);
int				is_a_directory(char *content);
int				is_permission_denied(char *content);
void			redirect_infile_outfile(t_pipes_ms *pipes, t_node_ms *node);

/****************/
/*	LINKED LIST	*/
/****************/

t_node_ms		*ft_lstnew_node(t_enum_token *operators);
t_token_ms		*ft_lstnew_token(void);
t_env_ms		*ft_lstnew_env_entry(const char *env);
void			initialize_node(t_node_ms *node);
t_env_ms		*lstnew_env_link(void);

/************/
/*	PARSING	*/
/************/

t_node_ms		*get_list_infos(t_node_ms *root, t_token_ms *tokens, \
					t_enum_token *operators);
t_node_ms		*get_mode_and_file(t_node_ms *binary_tree, \
					t_redir_ms *first_redir);
t_node_ms		*get_pipeline_infos(t_node_ms *root, t_token_ms *tokens, \
					t_enum_token *operators);
t_node_ms		*get_redirections_infos(t_node_ms *root, t_token_ms *tokens, \
					t_enum_token *operators);

t_node_ms		*left_branch(t_token_ms *tokens, t_enum_token oper, \
					t_enum_token *operators);
t_node_ms		*right_branch(t_token_ms *tokens, t_enum_token oper, \
					t_enum_token *operators);
t_node_ms		*manage_modes_and_files(t_node_ms *root);
t_node_ms		*start_binary_tree(t_token_ms *tokens);
t_node_ms		*build_binary_tree(t_token_ms *tokens, t_enum_token *operators);
t_token_ms		*fill_token(t_token_ms *tokens, char *user_input, \
					char *delim[10]);
t_token_ms		*parse_quotes(t_token_ms *tokens);
t_token_ms		**split_list(t_token_ms *tokens);
t_token_ms		*get_first_half(t_token_ms *tokens, int index_token);
t_token_ms		*get_second_half(t_token_ms *tokens);
t_token_ms		*lexer(char *user_input);
t_redir_ms		*get_redirections_list(t_token_ms *tokens);

/********************/
/*	DOLLAR_EXPAND	*/
/********************/

t_token_ms		*expand_var_with_dollar(t_token_ms *tokens_unparsed, \
					t_token_ms *tokens_parsed, t_env_ms *env_ll);
char			*get_new_content(char *parsed, char *key, char *value, \
					int nb_dollars);
char			*join_and_manage_dollar(char *parsed, \
					char *value, int key_len, int i);

/************/
/*	UTILS	*/
/************/

t_token_ms		*del_parenthesis_if_needed(t_token_ms *tokens);
t_env_ms		*convert_env_arr_into_ll(const char **env);
char			**convert_env_ll_into_arr(t_env_ms *env);
int				what_is_index_in(const char *user_input, int i);
int				what_is_dollar_in(const char *parsed, int i);
int				count_dollars_to_replace(char *content);
int				is_operator(t_enum_token type);
int				is_token_type_a_redir(t_enum_token token_type);
int				count_nb_of_tokens_left(t_token_ms *tokens);
char			*get_key_to_expand(char *content);
char			*get_key_value(t_env_ms *env_ll, char *key);
int				is_it_a_closed_quote(char *content, char quote);
int				is_dollar_inside_quotes(char *content, int i);
int				examine_dollar_conditions(char *content, int i);
int				get_nb_dollars(char *unparsed, int i);
int				get_index_delimiter(const char *user_input, char *delim[10], \
					int index);
int				token_content_length(char *user_input, char *delim[10]);
void			set_exit_code(t_env_ms *env_ll, int exit_code);
int				get_exit_code(t_env_ms *env_ll);
void			print_content_pipe(t_pipes_ms *pipes, t_env_ms *env_ll);
t_enum_token	identify_splitting_operator(t_token_ms *tokens);
t_enum_token	what_is_oper_in(t_token_ms *tokens);
t_enum_token	is_token_in_parenthesis(t_token_ms *tokens, int token_pos);
int				check_syntax_par(t_token_ms *tokens, t_env_ms *env_ll);
void			print_checking_error_msg(char *msg);
void			sort_env_ll(t_env_ms *env_ll);
int				count_args(char **content);
int				is_exit_value_out_of_range(char *content);
t_token_ms		*remove_empty_tokens(t_token_ms *tokens_parsed, \
					t_token_ms *tokens_unparsed);
void			set_dollar_underscore(t_env_ms *env_ll, char **content);
char			*get_dollar_underscore(t_env_ms *env_ll);
int				is_all_digit(char *content);
int				should_expand_this_dollar(char *content, int index);

/**************/
/*  BUILTINS  */
/**************/

int				ft_export(t_node_ms *node, t_env_ms *env_ll, t_pipes_ms *pipes);
int				check_errors_env_format(char *content);
int				set_values_export(char *content, t_env_ms *env_ll);
t_env_ms		*get_env(char *content);
int				ft_echo(t_node_ms *node, t_pipes_ms *pipes);
int				ft_cd(char **content, t_env_ms *env_ll);
int				ft_pwd(char *outfile, t_enum_token outfile_mode, \
					t_pipes_ms *pipes);
int				ft_env(t_node_ms *node, t_env_ms *env_ll, t_pipes_ms *pipes);
int				ft_unset(char **content, t_env_ms **env_ll);
int				change_value(char *content, t_env_ms *env_ll);
int				ft_exit(char **content, t_env_ms *env_ll, t_pipes_ms *pipes);

/************/
/*	FREE	*/
/************/

void			free_redirs_infos(t_node_ms *binary_tree);
void			free_redirs_list(t_redir_ms *first_redir);
void			free_splitted_tokens(t_token_ms **splitted_tokens);
void			free_tokens(t_token_ms *tokens);
void			free_env_list(t_env_ms *env);
void			free_binary_tree(t_node_ms *binary_tree);

#endif
