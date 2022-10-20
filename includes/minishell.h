#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd_ms
{
	char			*pipeline;
	char			*command;
	char			*options;
	char			*arguments;
	char			*redirection;
	char			*infile;
	char			*outfile;
}	t_cmd_ms;

/************/
/*	 MAIN	*/
/************/

//launch_program.c
int			launch_program(char *user_input);

//prompt.c
void		ft_signal(int sig);
int			cmd_prompt(char **env);

/********/
/*	SRC	*/
/********/

//highlight_syntax_error.c
void		highlight_syntax_error(const char *str, int start, int end);

/************/
/*	CHECK	*/
/************/

//ft_check_quotes.c
int			ft_check_isolated_quotes(const char *user_input);

//ft_check_ampersands.c
int			ft_check_isolated_ampersands(const char *user_input);

//ft_check_and_or_operators.c
int			are_all_and_or_operators_closed(const char *user_input);
int			ft_check_syntax_before_operators(const char *user_input, int i);

//ft_check_pipes.c
int			are_all_pipes_closed(const char *user_input);
int			ft_check_syntax_before_pipes(const char *user_input, int i);

//get_missing_user_input.c
char		*get_missing_user_input(char **user_input);

/************/
/*	PARSING	*/
/************/

//convert_var_with_dollar.c
char		*convert_var_with_dollar(char *user_input, char **env);

//utils_filter.c
int			check_space(char *user_input, int index);
int			what_is_character_in(const char *user_input, int i);

/************/
/*	INIT	*/
/************/

//init_struct_array.c
int			count_pipes(const char *user_input);
t_cmd_ms	*init_struct_array(const char *user_input);

/************/
/*	FREE	*/
/************/

//free.c
void		free_commands(t_cmd_ms *commands, int i);
#endif
