#include "../../includes/minishell.h"

/*static char	*join_strings_add_space(char *user_input, char *missing_input)
{
	char	*new_user_input;

	new_user_input = ft_strjoin_free_both(user_input, missing_input);
	return (new_user_input);
}*/

/************************************************************/
/*															*/
/*	Triggers an interactive mode and joins the provided		*/
/*		string to the user_input line						*/
/*															*/
/*	Parameters:												*/
/*		user_input	-	line from the terminal				*/
/*															*/
/*	Return:													*/
/*		new_user_input	-	the line newly formed line		*/
/*		NULL			-	an error occured				*/
/*															*/
/************************************************************/

char	*get_new_user_input(char *user_input)//Ajouter la gestion des signaux dans ce mode interactif
{
	char	*new_user_input;
	char	*missing_input;
	char	*err_msg;

	err_msg = "minishell: syntax error: unexpected end of file\nexit\n";
	missing_input = NULL;
	while (1)
	{
		missing_input = readline("> ");
		if (!missing_input)
		{
			write(2, err_msg, ft_strlen(err_msg));
			return (NULL);
		}
		else if (ft_strlen(missing_input) > 0)
		{
			new_user_input = ft_strjoin_free_second(user_input, missing_input);
			break ;
		}
	}
	return (new_user_input);
}
