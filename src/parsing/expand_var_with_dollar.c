#include "../../includes/minishell.h"

static int	check_if_dollar_is_isolated(char *content, int index_dollar)
{
	if (content[index_dollar + 1] == ' ')
		return (1);
	if (content[index_dollar + 1] == '$')
		return (1);
	if (content[index_dollar + 1] == '\0')
		return (1);
	return (0);
}

/************************************************************************/
/*                                                     					*/
/*  Deletes the $STRING in content because $STRING doesn't exist		*/
/*                                                     	 				*/
/*  Parameters:															*/
/*		content - line from the terminal								*/
/*		i - index of the '$' symbol found								*/
/*  Return:																*/
/*		MALLOC'ED content without $STRING							*/
/************************************************************************/
static char	*delete_dollar_from_line_if_needed(char *content, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	tmp = ft_calloc(sizeof(char), i);
	if (!tmp)
	{
		free(content);
		return (NULL);
	}
	ft_strncpy(tmp, content, i);
	i++;
	while (!ft_isspace(content[i + j]) && content[i + j] != '\"'
		&& content[i + j] != '$' && content[i + j] != '\0'
		&& content[i + j] != '\'' && !ft_isdigit(content[i + j - 1]))
		j++;
	tmp2 = ft_strjoin_free_first(tmp, content + i + j);
	free(content);
	return (tmp2);
}

/************************************************************************/
/*                                                     					*/
/*  Replaces the $STRING with env_variable in content				*/
/*                                                     	 				*/
/*  Parameters:															*/
/*		content - line from the terminal								*/
/*		env_var - line containing the env_variable whole line			*/
/*		i - index of the '$' symbol found								*/
/*  Return:																*/
/*		MALLOC'ED content with $STRING replace with its env_variable	*/
/************************************************************************/
static char	*replace_dollar_by_env_var(char *content, char *env_var, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	tmp = ft_calloc(sizeof(char), i);
	if (!tmp)
	{
		free(content);
		return (NULL);
	}
	ft_strncpy(tmp, content, i);
	while (env_var[j] != '=' && env_var[j] != '\0')
		j++;
	tmp2 = ft_strjoin_free_first(tmp, env_var + j + 1);
	if (!tmp2)
		return (NULL);
	tmp = ft_strjoin_free_first(tmp2, content + i + j + 1);
	free(content);
	return (tmp);
}

/************************************************************************/
/*                                                     					*/
/*  Extracts the env_variable if it exists and stores it in a string	*/
/*                                                     	 				*/
/*  Parameters:															*/
/*		content - line from the terminal								*/
/*		i - index of the '$' symbol found								*/
/*		env - env_variables												*/
/*  Return:																*/
/*		 MALLOC'ED string containing the env_variable whole line		*/
/************************************************************************/
static char	*extract_env_variable_line(char *content, int i, char **env)
{
	char	*var;
	int		j;

	j = 0;
	while (content[i + j] != ' ' && content[i + j] != '\"'
		&& content[i + j] != '$' && content[i + j] != '\0'
		&& content[i + j] != '\'')
		j++;
	var = ft_calloc(sizeof(char), j + 1);
	if (var == NULL)
		return (NULL);
	ft_strncpy(var, content + i, j);
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

/************************************************************/
/*                                                     		*/
/*  Determines if the environment variable found is valid	*/
/*	If it is, it will be changed. 							*/
/*	If it is not, it will be deleted from the line			*/
/*                                                     	 	*/
/*  Parameters:												*/
/*		content - line from the terminal					*/
/*		env - env variables									*/
/*	Example:												*/
/*		$USER bonjour -> kbrousse bonjour					*/
/*		$U bonjour -> bonjour								*/
/*  Return:													*/
/*		line with env_variable converted or deleted			*/
/************************************************************/
char	*expand_var_with_dollar(char *content, char **env)
{
	int		i;
	char	*env_var;

	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$' && what_is_dollar_in(content, i) == 0)
		{
			env_var = extract_env_variable_line(content, i + 1, env);
			if (env_var == NULL && !check_if_dollar_is_isolated(content, i))
				content = delete_dollar_from_line_if_needed(content, i);
			else if (env_var)
				content = replace_dollar_by_env_var(content, env_var, i);
			if (!content)
				return (NULL);
		}
		i++;
	}
	return (content);
}
