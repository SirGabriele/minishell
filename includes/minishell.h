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
	TOK_NULL,/*0*/
	TOK_STRING,/*1*/
	TOK_OP_PAR,/*2*/
	TOK_CL_PAR,/*3*/
	TOK_INFILE,/*4*/
	TOK_TRUNC,/*5*/
	TOK_HEREDOC,/*6*/
	TOK_APPEND,/*7*/
	TOK_PIPE,/*8*/
	TOK_AND_OPER,/*9*/
	TOK_OR_OPER,/*10*/
	TOK_SHELL,/*11*/
}	t_tokens;

/*typedef struct s_cmd_list_ms
{
	struct s_cmd_list_ms	*next;
	char					**cmd_and_args;
	char					*correct_path;
}	t_cmd_list_ms;*/

typedef struct s_env_ms
{
	struct s_env_ms			*next;
	char					*key;
	char					*value;
}	t_env_ms;

typedef struct s_redir_ms
{
	struct s_redir_ms		*next;
	char					*file_name;
	t_tokens				mode;	
}	t_redir_ms;

/*typedef struct s_all_redirs_ms
{
	struct s_redir_ms		*first_redir;
	char					*infile;
	char					*outfile;
	int						pipefd[2];
	t_tokens				infile_mode;
	t_tokens				outfile_mode;
}	t_all_redirs_ms;*/

typedef struct	s_node_ms
{
	struct s_node_ms		*left;
	struct s_node_ms		*right;
	struct s_redir_ms		*first_redir;
	char					**content;
	char					*infile;
	char					*outfile;
	t_tokens				infile_mode;
	t_tokens				outfile_mode;
	t_tokens				operator;
}	t_node_ms;

/*typedef struct s_context_ms
{
	struct s_context_ms		*next;
	struct s_all_redirs_ms	*all_redirs;
	t_tokens				what_is_pipeline_after;
	char					*pipeline;
}	t_context_ms;*/

typedef struct s_token_ms
{
	struct s_token_ms	*next;
	char				*content;
	t_tokens			type;
}	t_token_ms;

/************/
/*	SIGNALS	*/
/************/
void	ft_signal_user_input(int sig);

/********/
/*	SRC	*/
/********/

//prompt.c
void	ft_signal(int sig);
int		cmd_prompt(t_node_ms *root, t_env_ms *env);

//launch_program.c
int		launch_program(t_node_ms *root, char **user_input, t_env_ms *env);

//highlight_syntax_error.c
void	highlight_syntax_error(const char *str, int start, int end);

//free_program.c
void	free_program(t_node_ms *root, t_env_ms *env);

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
/*	INIT	*/
/************/

//init_root_struct.c
void  	 init_root_struct(t_node_ms *root);

/************/
/*	EXEC	*/
/************/

//simulate_struct.c
int		simulate_structs(t_node_ms *root, t_env_ms *env);

//print_structs.c
void	print_tree(t_node_ms *root);
void	print_env_ll(t_env_ms *env, char **env_real);
void	print_env_arr(char  **env, char **env_real);
void	print_pipe(int *pipe);

//launch_exec.c
int launch_exec(int *pipe_before, int *pipe_after, t_node_ms *root, t_env_ms *env);

//handle_all_redirs.c
int		handle_all_redirs(t_node_ms *node, int *pipe_before);

//heredoc_requested.c
int		heredoc_requested(t_redir_ms *redir, t_node_ms *node, int *pipe_before);

//execute_cmd.c
int		execute_cmd(int *pipe_before, int *pipe_after, t_node_ms *root, char **env);

/****************/
/*	LINKED LIST	*/
/****************/

/*//ft_lstnew_cmd
t_cmd_list_ms	*ft_lstnew_cmd(char *command_and_args);

//ft_lstnew_redir.c
t_redir_ms		*ft_lstnew_redir(char *file_name, t_tokens mode);

//init_structs.c
void			init_context_struct(t_context_ms *context);
void			init_context_all_redirs(t_all_redirs_ms *all_redirs);*/
//ft_lstnew_env_entry.c
t_env_ms	*ft_lstnew_env_entry(const char *env);
t_node_ms	*ft_create_node(void);
/************/
/*	UTILS	*/
/************/

//what_is_index_in.c
int			what_is_index_in(const char *user_input, int i);

//convert_env_into_ll.c
t_env_ms	*convert_env_into_ll(const char **env);

//convert_env_into_arr.c
char		**convert_env_into_arr(t_env_ms *env);

#endif
