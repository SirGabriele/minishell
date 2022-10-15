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

//launch_program.c
int	launch_program(char *user_input);
int	ft_check_quotes(char *user_input);

//prompt.c
void	ft_signal(int sig);
int	cmd_prompt(char **env);

//parsing.c
char	*convert_var_with_dollar(char *user_input, char **env);
char	*get_tmp_without_quotes(char *tmp, char *user_input);

//init
int    init_struct_array(const char *user_input);

#endif
