#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*	Extracts the env_variable if it exists and stores it in a		*/
/*		string														*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		key_to_expand	-	key of the command line					*/
/*		env_arr			-	double array containing env variables	*/
/*																	*/
/*  Return:															*/
/*		env_arr[i]	-	the env variable found						*/
/*		NULL		-	no env variable found						*/
/*																	*/
/********************************************************************/

static char	*extract_env_variable_line(char *key_to_expand, char **env_arr)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(key_to_expand);
	while (env_arr[i] != NULL)
	{
		if (ft_strncmp(key_to_expand, env_arr[i], j) == 0 && env_arr[i][j] == '=')
			break ;
		i++;
	}
	if (env_arr[i] == NULL)
	{
		free(key_to_expand);
		key_to_expand = NULL;
		return (NULL);
	}
	free(key_to_expand);
	key_to_expand = NULL;
	return (env_arr[i]);
}

static char	*get_key_to_expand(char *content)
{
	char	*key_to_expand;
	int		j;

	j = 0;
	while (content[j] != ' ' && content[j] != '\"'
		&& content[j] != '$' && content[j] != '\0'
		&& content[j] != '\'')
		j++;
	key_to_expand = malloc(sizeof(char) * (j + 1));
	if (key_to_expand == NULL)
	{
		perror(NULL);
		return (NULL);
	}
	ft_strncpy(key_to_expand, content, j);
	return (key_to_expand);
}

/****************************************************************/
/*                                                     			*/
/*  Verifies if the variable after the dollar sign is a valid	*/
/*		environment variable. If it is, the dollar is expanded.	*/
/*		Otherwise, the dollar and the variable are deleted from	*/
/*		the line												*/
/*                                                     	 		*/
/*  Parameters:													*/
/*		content	-	line from the terminal						*/
/*		env		-	env variables								*/
/*																*/
/*  Return:														*/
/*		content	-	the newly formed line						*/
/*																*/
/****************************************************************/

char	*expand_var_with_dollar(char *content, char **env_arr)
{
	char	*key_to_expand;
	char	*env_var;
	int		i;

	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$' && what_is_dollar_in(content, i) == 0)
		{
			key_to_expand = get_key_to_expand(content + i + 1);
			if (!key_to_expand)
			{
				free(content);
				return (NULL);
			}
			env_var = extract_env_variable_line(key_to_expand, env_arr);
			content = manage_dollar(env_var, content, i);
			if (!content)
				return (NULL);
		}
		if (content[i])
			i++;
	}
	return (content);
}
