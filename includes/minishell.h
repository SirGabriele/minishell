#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_context_mini
{
	int	single_quote;
	int	double_quote;
}	t_context_mini;

//prompt.c
void	ft_signal(int sig);
void	cmd_prompt(char **env);

//builtins.c
int		echo(char **str, char *options);

//parsing.c
char	*filter_cmd_line(char *user_input, char **env);
char	*convert_var_with_dollar(char *user_input, char **env);
char	*get_tmp_without_quotes(char *tmp, char *user_input);

#endif
