#include "../../includes/minishell.h"

/************************************************************************/
/*                                                     					*/
/*  Deletes the $STRING in parsed because $STRING doesn't exist		*/
/*                                                     	 				*/
/*  Parameters:															*/
/*		parsed - line from the terminal								*/
/*		i - index of the '$' symbol found								*/
/*  Return:																*/
/*		MALLOC'ED parsed without $STRING							*/
/************************************************************************/
static char	*delete_dollar_from_line(char *parsed, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	tmp = ft_calloc(sizeof(char), i + 1);
	if (!tmp)
	{
		ft_printf_error("Error happened in delete_dollar_from_line's malloc\n");
		free(parsed);
		return (NULL);
	}
	tmp = ft_strncpy(tmp, parsed, i);
	i++;
	while (parsed[i + j] != ' ' && parsed[i + j] != '\"'
		&& parsed[i + j] != '$' && parsed[i + j] != '\0'
		&& parsed[i + j] != '\'')
		j++;
	tmp2 = ft_strjoin_free_first(tmp, parsed + i + j);
	free(parsed);
	return (tmp2);
}

/************************************************************************/
/*                                                     					*/
/*  Replaces the $STRING with env_variable in parsed				*/
/*                                                     	 				*/
/*  Parameters:															*/
/*		parsed - line from the terminal								*/
/*		env_var - line containing the env_variable whole line			*/
/*		i - index of the '$' symbol found								*/
/*  Return:																*/
/*		MALLOC'ED parsed with $STRING replace with its env_variable	*/
/************************************************************************/
static char	*replace_dollar_by_env_var(char *parsed, char *env_var, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	tmp = ft_calloc(sizeof(char), i + 1);
	if (!tmp)
	{
		ft_printf_error("Error happened in replace_dollar"\
			"_with_env_var's malloc\n");
		free(parsed);
		return (NULL);
	}
	tmp = ft_strncpy(tmp, parsed, i);
	while (env_var[j - 1] != '=' && env_var[j] != '\0')
		j++;
	tmp2 = ft_strjoin_free_first(tmp, env_var + j);
	if (!tmp2)
		return (NULL);
	tmp = ft_strjoin_free_first(tmp2, parsed + i + j);
	free(parsed);
	return (tmp);
}

/************************************************************************/
/*                                                     					*/
/*  Extracts the env_variable if it exists and stores it in a string	*/
/*                                                     	 				*/
/*  Parameters:															*/
/*		parsed - line from the terminal								*/
/*		i - index of the '$' symbol found								*/
/*		env - env_variables												*/
/*  Return:																*/
/*		 MALLOC'ED string containing the env_variable whole line		*/
/************************************************************************/
static char	*extract_env_variable_line(char *parsed, int i, char **env)
{
	char	*var;
	int		j;

	j = 0;
	while (parsed[i + j] != ' ' && parsed[i + j] != '\"'
		&& parsed[i + j] != '$' && parsed[i + j] != '\0'
		&& parsed[i + j] != '\'')
		j++;
	var = ft_calloc(sizeof(char), j + 1);
	if (var == NULL)
		return (NULL);
	var = ft_strncpy(var, parsed + i, j);
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

static int	get_dollar_index(char *parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		if (parsed[i] == '$')
			return (i);
		i++;
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
/*		parsed - line from the terminal					*/
/*		env - env variables									*/
/*	Example:												*/
/*		$USER bonjour -> kbrousse bonjour					*/
/*		$U bonjour -> bonjour								*/
/*  Return:													*/
/*		line with env_variable converted or deleted			*/
/************************************************************/
char	*convert_var_with_dollar(char *parsed, char *content, char **env)
{
	int		i;
	int		index_dollar;
	char	*env_var;

	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$' && what_is_dollar_in(content, i) == 0)
		{
			index_dollar = get_dollar_index(parsed);
			env_var = extract_env_variable_line(parsed, index_dollar + 1, env);
			if (env_var == NULL)
				parsed = delete_dollar_from_line(parsed, index_dollar);
			else
				parsed = replace_dollar_by_env_var(parsed, env_var, index_dollar);
			if (!parsed)
				return (NULL);
		}
		i++;
	}
	return (parsed);
}
