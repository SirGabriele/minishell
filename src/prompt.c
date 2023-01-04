#include "../includes/minishell.h"

static void	free_user_input_and_set_to_null(char *user_input)
{
	free(user_input);
	user_input = NULL;
}

/************************************************************/
/*															*/
/*	Verifies if all characters that needs to be closed		*/
/*		or paired are, If not, an interactive mode is 		*/
/*		triggered until all the characters are closed 		*/
/*		or paired											*/
/*															*/
/*	Parameters:												*/
/*		user_input	-	line from the terminal				*/
/*															*/
/*	Return:													*/
/*		-1	-	an error occured							*/
/*		 0	-	the line has been correctly replaced		*/
/*															*/
/************************************************************/

static int	ft_check_closed_characters(char **user_input, t_env_ms *env_ll)
{
	int	ret_pipes;
	int	ret_par;

	ret_pipes = -1;
	ret_par = -1;
	while (ret_pipes == -1 || ret_par == -1)
	{
		ret_pipes = are_all_pipes_closed(*user_input);
		ret_par = are_all_parenthesis_paired(*user_input, env_ll);
		if (ret_pipes != -1 && ret_par != -1)
			break ;
		*user_input = get_missing_user_input(user_input);
		if (*user_input == NULL)
			return (-1);
		else
			continue ;
	}
	return (ret_par);
}

static int	ft_check_syntax_error(char **user_input, t_env_ms *env_ll)
{
	int	ret;

	ret = ft_check_closed_characters(user_input, env_ll);
	if (ret != 0)
	{
		free_user_input_and_set_to_null(*user_input);
		return (ret);
	}
	if (ft_check_isolated_quotes(*user_input) == -1)
		return (-1);
//	if (ft_check_shift_association(*user_input) == -1)
//		return (-1);// A FAIRE UNE FOIS LE LEXER OPERATIONNEL
//	if (ft_check_syntax_pipes(*user_input) == -1)
//		return (-1);// A FAIRE UNE FOIS LE LEXER OPERATIONNEL
//	if (ft_check_syntax_shifts(*user_input) == -1)
//		return (-1);// A FAIRE UNE FOIS LE LEXER OPERATIONNEL
	return (0);
}

static int	handle_prompt(char *user_input)
{
	if (!user_input)
	{
		rl_clear_history();
		write(1, "exit\n", 5);
		return (-1);
	}
	if (ft_strncmp(user_input, "exit", 4) == 0)
	{
		rl_clear_history();
		free_user_input_and_set_to_null(user_input);
		return (-1);
	}
	if (ft_strlen(user_input) > 0)
		add_history(user_input);
	return (0);
}

int	cmd_prompt(t_env_ms *env_ll)
{
	char	*user_input;
	char	*pwd_prompt;
	int		ret;

	while (1)
	{
		pwd_prompt = getcwd(NULL, 0);
		ft_printf("\e[1;96m%s\e[0m", pwd_prompt);
		user_input = readline("$ ");
		free(pwd_prompt);
		if (handle_prompt(user_input) == -1)
			return (0);
		ret = ft_check_syntax_error(&user_input, env_ll);
		if (ret == -1)
			return (-1);
		else if (ret == -2)
			continue ;
		if (launch_program(&user_input, env_ll) == -1)
		{
			free_user_input_and_set_to_null(user_input);
			return (-1);
		}
		else
			free_user_input_and_set_to_null(user_input);
	}
	return (3);
}
