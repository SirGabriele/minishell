#include "../../includes/minishell.h"

/************************************************************************/
/*                                                     					*/
/*  Deletes the $STRING in user_input because $STRING doesn't exist		*/
/*                                                     	 				*/
/*  Parameters:															*/
/*		user_input - line from the terminal								*/
/*		i - index of the '$' symbol found								*/
/*  Return:																*/
/*		MALLOC'ED user_input without $STRING							*/
/************************************************************************/
static char	*delete_dollar_from_line(char *user_input, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	tmp = ft_calloc(sizeof(char), i + 1);
	if (tmp == NULL)
	{
		ft_printf_error("Error happened in delete_dollar_from_line's malloc\n");
		free(user_input);
		exit(-1);
	}
	tmp = ft_strncpy(tmp, user_input, i);
	i++;
	while (user_input[i + j] != ' ' && user_input[i + j] != '\"'
		&& user_input[i + j] != '$' && user_input[i + j] != '\0'
		&& user_input[i + j] != '\'')
		j++;
	tmp2 = ft_strjoin(tmp, user_input + i + j);
	free(tmp);
	free(user_input);
	return (tmp2);
}

/************************************************************************/
/*                                                     					*/
/*  Replaces the $STRING with env_variable in user_input				*/
/*                                                     	 				*/
/*  Parameters:															*/
/*		user_input - line from the terminal								*/
/*		env_var - line containing the env_variable whole line			*/
/*		i - index of the '$' symbol found								*/
/*  Return:																*/
/*		MALLOC'ED user_input with $STRING replace with its env_variable	*/
/************************************************************************/
static char	*replace_dollar_by_env_var(char *user_input, char *env_var, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	tmp = ft_calloc(sizeof(char), i + 1);
	if (tmp == NULL)
	{
		ft_printf_error("Error happened in replace_dollar"\
			"_with_env_var's malloc\n");
		free(user_input);
		exit(-1); /d///sad virer l'exit
	}
	tmp = ft_strncpy(tmp, user_input, i);
	while (env_var[j - 1] != '=' && env_var[j] != '\0')
		j++;
	tmp2 = ft_strjoin(tmp, env_var + j);
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin(tmp2, user_input + i + j);
	free(tmp2);
	free(user_input);
	return (tmp);
}

/************************************************************************/
/*                                                     					*/
/*  Extracts the env_variable if it exists and stores it in a string	*/
/*                                                     	 				*/
/*  Parameters:															*/
/*		user_input - line from the terminal								*/
/*		i - index of the '$' symbol found								*/
/*		env - env_variables												*/
/*  Return:																*/
/*		 MALLOC'ED string containing the env_variable whole line		*/
/************************************************************************/
static char	*extract_env_variable_line(char *user_input, int i, char **env)
{
	char	*var;
	int		j;

	j = 0;
	while (user_input[i + j] != ' ' && user_input[i + j] != '\"'
		&& user_input[i + j] != '$' && user_input[i + j] != '\0'
		&& user_input[i + j] != '\'')
		j++;
	var = ft_calloc(sizeof(char), j + 1);
	if (var == NULL)
		return (NULL);
	var = ft_strncpy(var, user_input + i, j);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(var, env[i], j) == 0 && env[i][j] == '=')
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	free(var);
	var = NULL;
	return (env[i]);
}

/********************************************************************/
/*                                                     				*/
/*  Determines if the environment variable found is between			*/
/*	single/double quotes or not in any sort of quotes				*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input - line from the terminal							*/
/*		i - index of the '$' symbol found							*/
/*  Return:															*/
/*		0 - env_variable is between double quotes or alone			*/
/*		1 - env_variable is between single quotes					*/
/********************************************************************/
static int	what_is_dollar_in(char *user_input, int i)
{
	int		j;
	char	c;

	j = 0;
	while (user_input[j] != '\0')
	{
		if (user_input[j] == '\"' || user_input[j] == '\'')
		{
			c = user_input[j];
			j++;
			while (user_input[j] != c && user_input[j] != '\0')
				j++;
			if (j > i && c == '\"')
				return (0);
			else if (j > i && c == '\'')
				return (-1);
		}
		else if (user_input[j] == '$')
			return (0);
		j++;
	}
	return (-1);
}

/************************************************************/
/*                                                     		*/
/*  Determines if the environment variable found is valid	*/
/*	If it is, it will be changed. 							*/
/*	If it is not, it will be deleted from the line			*/
/*                                                     	 	*/
/*  Parameters:												*/
/*		user_input - line from the terminal					*/
/*		env - env variables									*/
/*	Example:												*/
/*		$USER bonjour -> kbrousse bonjour					*/
/*		$U bonjour -> bonjour								*/
/*  Return:													*/
/*		line with env_variable converted or deleted			*/
/************************************************************/
char	*convert_var_with_dollar(char *user_input, char **env)
{
	int		i;
	char	*env_var;

	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '$' && what_is_dollar_in(user_input, i) == 0)
		{
			env_var = extract_env_variable_line(user_input, i + 1, env);
			if (env_var == NULL)
				user_input = delete_dollar_from_line(user_input, i);
			else
				user_input = replace_dollar_by_env_var(user_input, env_var, i);
		}
		i++;
	}
	return (user_input);
}
