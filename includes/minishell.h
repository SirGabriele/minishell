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
	TOK_NULL, /*0*/
	TOK_STRING, /*1*/
	TOK_OP_PAR, /*2*/
	TOK_CL_PAR, /*3*/
	TOK_INFILE, /*4*/
	TOK_TRUNC, /*5*/
	TOK_HEREDOC, /*6*/
	TOK_APPEND, /*7*/
	TOK_PIPE, /*8*/
	TOK_AND_OPER, /*9*/
	TOK_OR_OPER, /*10*/
}	t_tokens;

typedef struct s_cmd_list_ms
{
	struct s_cmd_list_ms	*next;
	char					**cmd_and_args;
	char					*correct_path;
}	t_cmd_list_ms;

typedef struct s_redir_ms
{
	struct s_redir_ms		*next;
	char					*file_name;
	t_tokens				mode;	
}	t_redir_ms;

typedef struct s_all_redirs_ms
{
	struct s_redir_ms		*first_redir;
	char					*infile;
	char					*outfile;
	int						pipe_infile[2];
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
/*	EXEC	*/
/************/

//test_pipex.c
int				test_pipex(void);

//launch_pipex.c
int				launch_pipex(t_context_ms *context);

//exec_pipex.c
int				exec_pipex(t_context_ms *context);

//verify_infile_redirs.c
int				handle_append_infile(t_context_ms *context, t_redir_ms *cursor,
	const char *infile);
int				verify_basic_infile(t_redir_ms *cursor);

//heredoc_requested.c
int				real_heredoc_requested(t_context_ms *context, int std_in_copy);
int				fake_heredoc_requested(const char *delimiter, int std_in_copy);

//free_program.c
void			free_program(t_context_ms *context);

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

#endif
