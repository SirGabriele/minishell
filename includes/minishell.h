#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <signal.h>
///////////////
//	signal();
///////////////

# include <readline/readline.h>
# include <readline/history.h>
///////////////
//	readline;
///////////////

# include <fcntl.h>
////////////////
//	open
////////////////

# include <sys/wait.h>
///////////////
//	waipid
///////////////

typedef enum e_tokens
{
	TOK_NULL,
	TOK_STRING,
	TOK_OP_PAR,
	TOK_CL_PAR,
	TOK_INFILE,
	TOK_OUTF_TRUNC,
	TOK_HEREDOC,
	TOK_OUTF_APPEND,
	TOK_PIPE,
	TOK_AND_OPER,
	TOK_OR_OPER,
}	t_tokens;

typedef struct s_cmd_list_ms
{
	struct s_cmd_list_ms	*next;
	char					**cmd_and_args;
	char					*correct_path;
}	t_cmd_list_ms;

typedef struct s_redir_ms
{
	struct s_redir_ms	*next;
	char					*file_name;
	t_tokens				mode;	
}	t_redir_ms;

typedef struct s_all_redirs_ms
{
	struct s_redir_ms		*first_redir;
	char					*infile;
	char					*outfile;
	t_tokens				infile_mode;
	t_tokens				outfile_mode;
}	t_all_redirs_ms;

typedef struct s_context_ms
{
	struct s_context_ms		*next;
	struct s_all_redirs_ms	*all_redirs;
	t_tokens				what_is_pipeline_after;
	char					*pipeline;
}	t_context_ms;

typedef struct s_token_ms
{
	struct s_token_ms	*next;
	char				*content;
	t_tokens			type;
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
/*	EXEC	*/
/************/

//test_pipex.c
int				test_pipex(void);

//launch_pipex.c
int				launch_pipex(t_context_ms *context);

//exec_pipex.c
int				exec_pipex(t_context_ms *context);

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

//ft_lstnew_redir.c
t_redir_ms		*ft_lstnew_redir(char *file_name, t_tokens mode);

//init_structs.c
void			init_context_struct(t_context_ms *context);
void			init_context_all_redirs(t_all_redirs_ms *all_redirs);

/************/
/*	UTILS	*/
/************/

//what_is_index_in.c
int				what_is_index_in(const char *user_input, int i);

//get_nb_tokens.c
int				get_nb_tokens(const char *user_input, char **delimiters);

#endif
