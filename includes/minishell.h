#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
///////////////
//	signal();
///////////////
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
//////////////
//	readline
//////////////

typedef struct s_cmd_list_ms
{
	char			*command;
	char			*options;
	char			*arguments;
	char			*infile;
	char			*outfile;
	struct s_cmd_list_ms	*next;
}	t_cmd_list_ms;

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

//ft_check_shifts.c
int	ft_check_shift_association(const char *user_input);
int	ft_check_syntax_shifts(const char *user_input);

//ft_check_pipes.c
int	are_all_pipes_closed(const char *user_input);
int	ft_check_syntax_before_character(const char *user_input, int i, const char *character);
int	what_is_index_in(const char *user_input, int i);
int	is_previous_syntax_valid(const char *user_input, int i);

//get_missing_user_input.c
char	*get_missing_user_input(char **user_input);

/************/
/*	PARSING	*/
/************/
//convert_var_with_dollar.c
char	*convert_var_with_dollar(char *user_input, char **env);

//utils_filter.c
char	*get_tmp_without_quotes(char *tmp, char *user_input);

#endif
