#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"

/************/
/*	CHECK	*/
/************/

//check_paired_characters.c
int				are_all_pipes_closed(const char *user_input);
int				are_all_parenthesis_paired(const char *user_input);

//ft_check_quotes.c
int				ft_check_isolated_quotes(const char *user_input);

//ft_check_forbidden_characters.c
int				ft_check_forbidden_characters(const char *user_input);

//ft_check_isolated_ampersands.c
int				ft_check_isolated_ampersands(const char *user_input);

//ft_check_pipes.c
int				ft_check_syntax_before_character(const char *user_input, \
					int i, const char *character);
int				what_is_index_in(const char *user_input, int i);
int				is_previous_syntax_valid(const char *user_input, int i);

//get_missing_user_input.c
char			*get_missing_user_input(char **user_input);

/********/
/*	SRC	*/
/********/
//launch_program.c
int				launch_program(char **user_input, char **env);

//prompt.c
void			ft_signal(int sig);
int				cmd_prompt(char **env);

//highlight_syntax_error.c
void			highlight_syntax_error(const char *str, int start, int end);

/************/
/*	PARSING	*/
/************/

//binary_tree.c
t_node_ms		*build_binary_tree(t_token_ms *tokens, t_tokens what_shell);

//binary_tree_utils.c
t_tokens		check_token_pos(t_token_ms *tokens, int token_pos);
t_tokens		detect_operators(t_token_ms *tokens);
t_tokens		identify_operator(t_token_ms *tokens);
t_token_ms		*supp_parenthesis_if_needed(t_token_ms *tokens);
int				check_parenthesis(t_token_ms *tokens);

//free.c
void			free_user_input_and_set_to_null(char *user_input);
void			free_tokens(t_token_ms *tokens);

//ft_lst.c
t_token_ms		*lst_fill(t_token_ms *tokens, char *user_input, char *delim[10]);
t_token_ms		*lstnew_token(void);

//get_list_infos.c
t_node_ms		*get_list_infos(t_token_ms *tokens, t_tokens what_shell);

//get_pipeline_infos.c
t_node_ms		*get_pipeline_infos(t_token_ms *tokens, t_tokens what_shell);

//get_tokens.c
t_token_ms		*get_tokens(char *user_input, char *delim[10]);

//lexer.c
t_token_ms		*lexer(char *user_input);

//parse_spaces.c
char			*parse_spaces(char *pipeline, t_token_ms *tokens);

//parsing.c
t_token_ms		*parsing(t_token_ms *tokens, char **env);

//utils_tokens.c
int				token_length(char *user_input, char *delim[10]);
int				is_a_delimiter(const char *user_input, char *delim[10], int index);
t_tokens		identify_delim_token(char *user_input, char *delim[10]);

//convert_var_with_dollar.c
char			*convert_var_with_dollar(char *parsed, char *content, char **env);

//dollar_utils.c
int				what_is_dollar_in(const char *parsed, int i);

//get_redirections.c
t_node_ms		*get_redirections_infos(t_token_ms *tokens);

//get_redirections_list.c
t_redir_ms		*get_redirections_list(t_token_ms *tokens);
 //get_redirections_modes_and_files.c
t_node_ms		*get_redirections_modes_and_files(t_node_ms *binary_tree);

/************/
/*	UTILS	*/
/************/

//what_is_index_in.c
int				what_is_index_in(const char *user_input, int i);

#endif
