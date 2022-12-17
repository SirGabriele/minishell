#include "../../includes/minishell.h"

static int	ft_check_special_characters(const char *user_input)
{
	char	*err_msg;
	int		i;

	err_msg = "minishell: syntax error\n";
	i = 0;
	while (user_input[i] != '\0')
	{
		if ((user_input[i] == '#' || user_input[i] == '!'
				|| user_input[i] == '`' || user_input[i] == '['
				|| user_input[i] == '{' || user_input[i] == '}')
			&& what_is_index_in(user_input, i) == 0)
		{
			write (2, err_msg, ft_strlen(err_msg));
			highlight_syntax_error(user_input, i, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

/************************************************************/
/*															*/
/*	Checks is a forbidden symbol is in the user_input line	*/
/*															*/
/*	Parameters:												*/
/*		user_input	-	line from the terminal         		*/
/*															*/
/*	Return:													*/
/*		-1	-	a forbidden character is detected			*/
/*		 0	-	no forbidden character is detected 			*/
/*															*/
/************************************************************/

int	ft_check_forbidden_characters(const char *user_input)
{
	if (ft_check_special_characters(user_input) == -1)
		return (-1);
	return (0);
}
