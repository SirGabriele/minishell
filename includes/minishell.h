#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"

/********/
/*	SRC	*/
/********/
//launch_program.c
int				launch_program(char **user_input);

//prompt.c
void			ft_signal(int sig);
int				cmd_prompt(char **env);

//highlight_syntax_error.c
void			highlight_syntax_error(const char *str, int start, int end);

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

/************/
/*	PARSING	*/
/************/

//lexer.c
t_token_ms		*lexer(char *user_input);

//get_tokens.c
t_token_ms		*get_tokens(char *user_input, char *delim[7]);

//ft_lst.c
t_token_ms		*lst_fill(t_token_ms *tokens, char *user_input, char *delim[7]);
t_token_ms		*lstnew_token(void);
t_context_ms	*lstnew_cmd_lst(void);

//utils_tokens.c
int				token_length(char *user_input, char *delim[7]);
int				is_a_delimiter(const char *user_input, char *delim[7], int index);
t_tokens		identify_delim_token(char *user_input, char *delim[7]);

//parsing.c
t_context_ms	*parsing(t_token_ms *tokens);

//structure_cmd_line.c
t_context_ms	*structure_cmd_lst(t_token_ms *tokens);

//get_pipelines.c
int				get_all_pipelines(t_token_ms *tokens, t_context_ms *cmd_lst);

//get_pipelines_utils.c
t_token_ms		*increm_tokens_copy(t_token_ms *tokens_cpy);
int				length_without_spaces(char *pipeline);
char			*add_space_if_needed(char *pipeline, t_token_ms *tokens);
char			*parse_spaces(char *pipeline, t_token_ms *tokens);

//free_1.c
void			free_user_input_and_set_to_null(char *user_input);
void			free_lst_content(t_token_ms *tokens);
void			free_tokens(t_token_ms *tokens);

//free_2.c
void			free_redirections(t_redir_list_ms *redir_list);
void			free_all_redirections(t_all_redir_ms *all_redirs);
void			free_context(t_context_ms *cmd_lst);

/************/
/*	UTILS	*/
/************/

//what_is_index_in.c
int				what_is_index_in(const char *user_input, int i);

#endif
