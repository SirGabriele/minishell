#include "../../includes/minishell.h"

static int	is_quote_closed(const char *user_input, int i)
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
/*		0 - no isolated quote is detected					*/
/*		1 - an isolated quote is detected					*/
/*															*/
/************************************************************/
int	ft_check_isolated_quotes(const char *user_input)
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
				ft_printf_error("minishell syntax error\n");
				highlight_syntax_error(user_input, i, i);
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
