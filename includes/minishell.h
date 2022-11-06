#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
///////////////
//	signal();
///////////////

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
///////////////
//	readline;
///////////////

typedef enum e_tokens
{
	TOK_NULL,
	TOK_STRING,
	TOK_OP_PAR,
	TOK_CL_PAR,
	TOK_INF_REDIR,
	TOK_OUTF_TRUNC,
	TOK_HEREDOC,
	TOK_OUTF_APPEND,
	TOK_PIPE,
	TOK_AND_OPER,
	TOK_OR_OPER,
}	t_tokens;

typedef struct s_cmd_list_ms
{
	char					**to_create_trunc;
	char					*to_create_append;
	char					*infile;
	char					*outfile;
	char					*outfile_mode;
	char					*command;
	char					*options;
	char					*arguments;
	struct s_cmd_list_ms	*next;
}	t_cmd_list_ms;

typedef struct s_token_ms
{
	char				*type;
	char				*content;
	struct s_token_ms	*next;
}	t_token_ms;

/********/
/*	SRC	*/
/********/
//launch_program.c
int		launch_program(char **user_input);

//prompt.c
void	ft_signal(int sig);
int		cmd_prompt(char **env);

//highlight_syntax_error.c
void	highlight_syntax_error(const char *str, int start, int end);

/************/
/*	CHECK	*/
/************/

//check_paired_characters.c
int		are_all_pipes_closed(const char *user_input);
int		are_all_parenthesis_paired(const char *user_input);

//ft_check_quotes.c
int		ft_check_isolated_quotes(const char *user_input);

//ft_check_forbidden_characters.c
int		ft_check_forbidden_characters(const char *user_input);

//ft_check_isolated_ampersands.c
int		ft_check_isolated_ampersands(const char *user_input);

//ft_check_pipes.c
int		ft_check_syntax_before_character(const char *user_input, \
		int i, const char *character);
int		what_is_index_in(const char *user_input, int i);
int		is_previous_syntax_valid(const char *user_input, int i);

//get_missing_user_input.c
char	*get_missing_user_input(char **user_input);

/************/
/*	PARSING	*/
/************/

//lexer.c
int		lexer(t_token_ms **arr_tokens, const char *user_input);

/************/
/*	UTILS	*/
/************/

//what_is_index_in.c
int		what_is_index_in(const char *user_input, int i);

//get_nb_tokens.c
int		get_nb_tokens(const char *user_input, char **delimiters);

#endif
