#include "../../includes/minishell.h"

static void	highlight_syntax_error(const char *str, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (k < 2)
	{
		while (str[j])
		{
			if (j != i && k == 0)
				ft_printf("%c", str[j]);
			else if (j != i && k == 1)
				ft_printf(" ");
			if (j == i && k == 0)
				ft_printf("\e[1;91m%c\e[0m", str[j]);
			else if (j == i && k == 1)
				ft_printf("\e[1;91m^\e[0m");
			j++;
		}
		ft_putchar('\n');
		j = 0;
		k++;
	}
}

static int	is_quote_closed(char *user_input, int i)
{
	int	j;

	j = i + 1;
	while (user_input[j] != user_input[i] && user_input[j] != '\0')
		j++;
	if (user_input[j] == '\0')
		return (-1);
	return (0);
}

/************************************************************/
/*															*/
/*	Detects all isolated quote and deletes it from the line	*/
/*															*/
/*	Parameters:												*/
/*		user_input - line from the terminal         		*/
/*	Return:													*/
/*		MALLOC'ED line without all isolated quotes			*/
/*															*/
/************************************************************/
int	ft_check_quotes(char *user_input)
{
	int		i;
	char	save;

	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '\"' || user_input[i] == '\'')
		{
			save = user_input[i];
			if (is_quote_closed(user_input, i) == -1)
			{
				ft_printf_error("Error - Unclosed quote detected\n");
				highlight_syntax_error(user_input, i);
				return (-1) ;
			}
			i++;
			while (user_input[i] != save)
				i++;
		}
		i++;
	}
	return (0);
}

/*char	*filter_cmd_line(char *user_input, char **env)
{
	user_input = convert_var_with_dollar(user_input, env);
	while (user_input[i] != '\0')
	{
//		if (user_input[i] == '\"')
	//		user_input = convert_var_with_dollar(user_input, env);
		if (user_input[i] == '$')
			user_input = conver_var_with_dollar(user_input, env);
		i++;
	}
	//user_input = delete_closed_quotes(user_input);	
	return (user_input);
}*/
