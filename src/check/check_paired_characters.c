#include "../../includes/minishell.h"

static int	count_nb_charac(const char *user_input, const char charac)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == charac && what_is_index_in(user_input, i) == 0)
			count++;
		i++;
	}
	return (count);
}

static void	display_error(const char *user_input, int i, t_env_ms *env_ll)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
	highlight_syntax_error(user_input, i, i);
	set_exit_code(env_ll, 2);
}

/************************************************************/
/*															*/
/*	Verifies if all the pipes are closed					*/
/*															*/
/*	Parameters:												*/
/*		user_input	-	line from the terminal				*/
/*															*/
/*	Return:													*/
/*		-1	-	a pipe is not closed						*/
/*		 0	-	all pipes are closed						*/
/*															*/
/************************************************************/

int	are_all_parenthesis_paired(const char *user_input, t_env_ms *env_ll)
{
	int	i;
	int	last_closing_par;
	int	nb_opening_par;
	int	nb_closing_par;

	i = 0;
	last_closing_par = 0;
	nb_opening_par = count_nb_charac(user_input, '(');
	nb_closing_par = count_nb_charac(user_input, ')');
	if (nb_opening_par > nb_closing_par)
		return (-1);
	else if (nb_opening_par < nb_closing_par)
	{
		i = 0;
		while (user_input[i] != '\0')
		{
			if (user_input[i] == ')' && what_is_index_in(user_input, i) == 0)
				last_closing_par = i;
			i++;
		}
		display_error(user_input, last_closing_par, env_ll);
		return (-2);
	}
	return (0);
}

/************************************************************/
/*															*/
/*	Verifies if all the pipes are closed					*/
/*															*/
/*	Parameters:												*/
/*		user_input	-	line from the terminal				*/
/*															*/
/*	Return:													*/
/*		-1	-	a pipe is not closed						*/
/*		 0	-	all pipes are closed						*/
/*															*/
/************************************************************/
int	are_all_pipes_closed(const char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (user_input[i] == '|')
		{
			i++;
			while (ft_isprint(user_input[i]) == 0 && user_input[i] != '\0')
				i++;
			if (user_input[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (0);
}
