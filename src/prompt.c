#include "../includes/minishell.h"

/*static void	free_user_input_and_set_to_null(char *user_input)
{
	free(user_input);
	user_input = NULL;
}*/

static int	check_syntax_pipe(t_token_ms *tokens_unparsed)
{
	if (tokens_unparsed->type == TOK_PIPE)
	{
//		set_exit_code(env_ll, 2);
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return (-1);
	}
	while (tokens_unparsed != NULL)
	{
		if (tokens_unparsed->type == TOK_PIPE && tokens_unparsed->next
			&& tokens_unparsed->next->type == TOK_PIPE)
		{
//			set_exit_code(env_ll, 2);
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				return (-1);
		}
		tokens_unparsed = tokens_unparsed->next;
	}
	return (0);
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

//static int	ft_check_closed_characters(char **user_input/*, t_env_ms *env_ll*/, t_token_ms *tokens_unparsed)
//{
//	char	*new_user_input;
//	int		ret_pipes;
//	int		ret_par;
//	int		ret;

//	ret = 0;
//	ret_pipes = -1;
//	ret_par = -1;
//	while (ret_pipes == -1 || ret_par == -1)
//	{
//	if (check_syntax_pipe(tokens_unparsed, env_ll) == -1)
//		return (-1);
//	if (is_last_pipes_closed(tokens_unparsed) == -1)
//	{
//		new_user_input = get_new_user_input(*user_input);
//		if (new_user_input == NULL)
//			return (-1);
//		else
//		{
//			*user_input = ft_strdup(new_user_input);
//			free(new_user_input);
//		}
//	}
//	if (are_all_parenthesis_paired(*user_input, env_ll) == -1)//A LAISSER
//		ret = -1;
//	if (ret == 0)
//		return (0);
//		if (ret_pipes != -1 && ret_par != -1)
//			break ;
/*	else
	{
		new_user_input = get_new_user_input(*user_input);
		if (new_user_input == NULL)
			return (-1);
		else
		{
			*user_input = ft_strdup(new_user_input);
			free(new_user_input);
//				continue ;
		}
	}*/
//	return (ret);
//}*/

static int	ft_check_syntax_error(char **user_input, t_env_ms *env_ll)
{
	t_token_ms	*tokens_unparsed;
	char		*new_user_input;
	int			ret;
	(void)env_ll;

	ret = 1;
	while (ret != 0)
	{
		ret = 0;
		if (ft_check_isolated_quotes(*user_input, env_ll) == -1)
			return (-1);
		tokens_unparsed = lexer(*user_input);
		if (!tokens_unparsed)
			return (-1);
		if (check_syntax_error(tokens_unparsed) == -1)
		{
			free_tokens(tokens_unparsed);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		if (check_syntax_pipe(tokens_unparsed) == -1)
		{
			free_tokens(tokens_unparsed);
			set_exit_code(env_ll, 2);
			return (-1);
		}
		if (is_last_pipes_closed(tokens_unparsed) == -1)
		{
			new_user_input = get_new_user_input(*user_input);
			if (new_user_input == NULL)
			{
				free_tokens(tokens_unparsed);
				return (-1);
			}
			else
			{
				free(*user_input);
				*user_input = ft_strdup(new_user_input);
				free(new_user_input);
				ret = -1;
			}
		}
		//checker les parentheses
/*		if (ft_check_closed_characters(user_input, env_ll, tokens_unparsed) == -1)
		{
			free_tokens(tokens_unparsed);
			return (-1) ;
		}*/
		free_tokens(tokens_unparsed);
	}
	return (0);
}

static int	is_exit(char *user_input)
{
	if (!user_input)
	{
		rl_clear_history();
		write(1, "exit\n", 5);
		return (0);
	}
	if (ft_strncmp(user_input, "exit", 4) == 0)
	{
		rl_clear_history();
		free(user_input);
		return (0);
	}
	return (1);
}

int	cmd_prompt(t_env_ms *env_ll)
{
	char	*user_input;
	char	*pwd_prompt;
	int		ret;

	while (1)
	{
		pwd_prompt = get_pwd_prompt(env_ll);
		user_input = readline(pwd_prompt);
		free(pwd_prompt);
		if (is_exit(user_input) == 0)
			return (0);
		ret = ft_check_syntax_error(&user_input, env_ll);
		if (ft_strlen(user_input) > 0)
			add_history(user_input);
		if (ret != 0)
			continue ;
		if (launch_program(&user_input, env_ll) == -1)
			return (-1);
	}
	return (3);
}
