#include "../includes/minishell.h"

/************************************************************/
/*															*/
/*	Verifies if all characters that needs to be closed		*/
/*		or paired are, If not, an interactive mode is 		*/
/*		triggered until all the characters are closed 		*/
/*		or paired											*/
/*															*/
/*	Parameters:												*/
/*		user_input - line from the terminal					*/
/*															*/
/*	Return:													*/
/*		-1 - an error occured								*/
/*		 0 - the line has been correctly replaced			*/
/*															*/
/************************************************************/

static int	ft_check_closed_characters(char **user_input)
{
	while (are_all_pipes_closed(*user_input) == -1
		|| are_all_parenthesis_paired(*user_input) == -1)
	{
		*user_input = get_missing_user_input(user_input);
		if (*user_input == NULL)
			return (-1);
		else
			continue ;
	}
	return (0);
}

/*static int	ft_check_syntax_pipes(const char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '|' && user_input[i + 1] == '|'
			&& (what_is_index_in(user_input, i)) == 0)
		{
			ft_printf("Syntax error\n");// changer tous les printf end printf_fd
			highlight_syntax_error(user_input, i + 1, i + 1);
			return (-1);
		}
		if (user_input[i] == '|' && what_is_index_in(user_input, i) == 0)
		{
			if (ft_check_syntax_before_character(user_input, i, "|") == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}*/

static int	ft_check_syntax_error(char **user_input)
{
	if (ft_check_closed_characters(user_input) == -1)
		return (-1);
	if (ft_check_isolated_quotes(*user_input) == -1)
		return (-1);
	if (ft_check_forbidden_characters(*user_input) == -1)
		return (-1);
//	if (ft_check_shift_association(*user_input) == -1)
//		return (-1);// A FAIRE UNE FOIS LE LEXER OPERATIONNEL
//	if (ft_check_syntax_pipes(*user_input) == -1)
//		return (-1);// A FAIRE UNE FOIS LE LEXER OPERATIONNEL
//	if (ft_check_syntax_shifts(*user_input) == -1)
//		return (-1);// A FAIRE UNE FOIS LE LEXER OPERATIONNEL
	return (0);
}

int	launch_program(char **user_input)
{

	if (ft_check_syntax_error(user_input) == -1)
		return (-1);
	(void)user_input;
	if (test_pipex() == -1)
		return (-1);
	return (0);
}
