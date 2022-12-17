#include "../../includes/minishell.h"

/************************************************************/
/*															*/
/*	Detects all isolated ampersands 						*/
/*															*/
/*	Parameters:												*/
/*		user_input - line from the terminal         		*/
/*															*/
/*	Return:													*/
/*		0 - no isolated ampersand is detected				*/
/*		1 - an isolated ampersand is detected				*/
/*															*/
/************************************************************/
int	ft_check_isolated_ampersands(const char *user_input)
{
	char	*err_msg;
	int		i;

	err_msg = "minishell: syntax error\n";
	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '&' && user_input[i + 1] != '&'
			&& what_is_index_in(user_input, i) == 0)
		{
			write (2, err_msg, ft_strlen(err_msg));
			highlight_syntax_error(user_input, i, i);
			return (-1);
		}
		if (user_input[i] == '&' && user_input[i + 1] == '&')
			i++;
		i++;
	}
	return (0);
}
