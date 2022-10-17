#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd_list_ms
{
	char			*command;
	char			*options;
	char			*arguments;
	char			*infile;
	char			*outfile;
	struct s_cmd_list_ms	*next;
}	t_cmd_list_ms;

typedef struct s_pipelines_ms
{
	char			*list;
	struct s_cmd_list_ms	*first_cmd;
}	t_pipelines_ms;

/********/
/*	SRC	*/
/********/
//launch_program.c
int	launch_program(char **user_input);

//prompt.c
void	ft_signal(int sig);
int	cmd_prompt(char **env);

//highlight_syntax_error.c
void	highlight_syntax_error(const char *str, int start, int end);

/************/
/*	CHECK	*/
/************/

//ft_check_quotes.c
int	ft_check_isolated_quotes(const char *user_input);

//ft_check_ampersands.c
int	ft_check_isolated_ampersands(const char *user_input);

//ft_check_triple_and_or.c
int	ft_check_triple_and_or(const char *user_input);

//ft_check_and_or_operators.c
int	are_all_and_or_operators_closed(const char *user_input);
int	ft_check_syntax_before_operators(const char *user_input);

//ft_check_pipes.c
int	are_all_pipes_closed(const char *user_input);
int	ft_check_syntax_before_pipes(const char *user_input);

//get_missing_user_input.c
char	*get_missing_user_input(char **user_input);

/************/
/*	PARSING	*/
/************/
//convert_var_with_dollar.c
char	*convert_var_with_dollar(char *user_input, char **env);

//utils_filter.c
char	*get_tmp_without_quotes(char *tmp, char *user_input);

/************/
/*	INIT	*/
/************/
//init_struct_array
int    init_struct_array(const char *user_input);

#endif
