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
	char					**command_and_args;
	struct s_cmd_list_ms	*next;
}	t_cmd_list_ms;

typedef struct s_pipeline_ms
{
	char					**to_create_trunc;// size du tableau == number_if_>_token
	char					**to_create_append;//size du tableau == number_of_>>_token
	char					*infile;
	char					*outfile;
	int						outfile_mode;
	struct s_cmd_list_ms	*first_cmd;
}	t_pipeline_ms;

typedef struct s_token_ms
{
	int					type;
	char				*content;
	struct s_token_ms	*next;
}	t_token_ms;

/********/
/*	SRC	*/
/********/
//launch_program.c
int		launch_program(char **user_input);
void	test_pipex(void);

//prompt.c
void	ft_signal(int sig);
int		cmd_prompt(char **env);

//highlight_syntax_error.c
void	highlight_syntax_error(const char *str, int start, int end);

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
int				lexer(t_token_ms **arr_tokens, const char *user_input);

/****************/
/*	LINKED LIST	*/
/****************/

//ft_lstnew_cmd
t_cmd_list_ms	*ft_lstnew_cmd(char *command_and_args);

//init_pipeline_struct.c
void			init_pipeline_struct(t_pipeline_ms *pipeline);

/************/
/*	UTILS	*/
/************/

//what_is_index_in.c
int				what_is_index_in(const char *user_input, int i);

//get_nb_tokens.c
int				get_nb_tokens(const char *user_input, char **delimiters);

#endif
