#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"
# include "struct.h"

/************/
/*	CHECK	*/
/************/

int				are_all_pipes_closed(const char *user_input);
int				are_all_parenthesis_paired(const char *user_input);
int				ft_check_isolated_quotes(const char *user_input);
int				ft_check_forbidden_characters(const char *user_input);
int				ft_check_isolated_ampersands(const char *user_input);
int				ft_check_syntax_before_character(const char *user_input, \
					int i, const char *character);
int				what_is_index_in(const char *user_input, int i);
int				is_previous_syntax_valid(const char *user_input, int i);
char			*get_missing_user_input(char **user_input);

/********/
/*	SRC	*/
/********/

int				launch_program(char **user_input, char **env);
void			ft_signal(int sig);
int				cmd_prompt(char **env);
void			highlight_syntax_error(const char *str, int start, int end);

/************/
/*	 FREE	*/
/************/

void			free_tokens(t_token_ms *tokens);
void			free_splited_tokens(t_token_ms **splited_tokens);
void			free_redirs_list(t_redir_ms *first_redir);
void			free_redirs_infos(t_node_ms *binary_tree);
void			free_binary_tree(t_node_ms *binary_tree);
void			free_double(char **double_str);
void			free_env_list(t_env_ms *env);

/************/
/* PARSING	*/
/************/

t_node_ms		*build_binary_tree(t_token_ms *tokens, t_enum_token what_shell, \
					t_enum_token *operators);
t_node_ms		*start_binary_tree(t_token_ms *tokens);
t_enum_token	check_token_pos(t_token_ms *tokens, int token_pos);
t_enum_token	what_is_oper_in(t_token_ms *tokens);
t_enum_token	identify_splitting_operator(t_token_ms *tokens);
t_token_ms		*del_parenthesis_if_needed(t_token_ms *tokens);
int				check_parenthesis(t_token_ms *tokens);
t_token_ms		*fill_token(t_token_ms *tokens, char *user_input, \
					char *delim[11], char **env);
t_token_ms		*lstnew_token(void);
t_node_ms		*right_branch(t_token_ms *tokens, t_enum_token oper, \
					t_enum_token shell, t_enum_token *operators);
t_node_ms		*left_branch(t_token_ms *tokens, t_enum_token oper, \
					t_enum_token shell, t_enum_token *operators);
t_node_ms		*get_list_infos(t_token_ms *tokens, t_enum_token what_shell, \
					t_enum_token *operators);
t_token_ms		**split_list(t_token_ms *tokens);
t_token_ms		*get_first_half(t_token_ms *tokens, int index_token);
t_token_ms		*get_second_half(t_token_ms *tokens);
int				is_operator(t_enum_token type);
t_node_ms		*get_pipeline_infos(t_token_ms *tokens, t_enum_token shell, \
					t_enum_token *operators);
t_token_ms		*lexer(char *user_input, char **env);
t_token_ms		*parse_quotes(t_token_ms *tokens);
int				token_content_length(char *user_input, char *delim[11]);
int				get_index_delimiter(const char *user_input, char *delim[11], \
					int index);
t_enum_token	identify_delim_token(int index_delim);
int				count_nb_of_tokens_left(t_token_ms *tokens);
int				check_if_token_is_redir(t_enum_token token_type);
char			*expand_var_with_dollar(char *content, char **env);
char			*extract_env_variable_line(char *var, char **env);
char			*get_var_to_look_for(char *content);
char			*manage_dollar(char *env_var, char *content, int i);
int				what_is_dollar_in(const char *parsed, int i);
t_node_ms		*get_redirections_infos(t_token_ms *tokens, \
					t_enum_token *operators);
t_redir_ms		*get_redirections_list(t_token_ms *tokens);
t_node_ms		*manage_modes_and_files(t_node_ms *binary_tree);
t_node_ms		*get_mode_and_file(t_node_ms *binary_tree, \
					t_redir_ms *first_redir);
t_token_ms		*del_redirections(t_token_ms *tokens);
int				what_is_index_in(const char *user_input, int i);

/****************/
/*	 BUILTINS	*/
/****************/

int				ft_echo(char **content);
int				ft_cd(char **content);
int				ft_pwd(void);
int				ft_env(char **content, t_env_ms *env);
int				ft_export(char **content, t_env_ms *env);
t_env_ms		*set_values_export(char **content, t_env_ms *env);
t_env_ms		*get_env(char *content, t_env_ms *env);

#endif
