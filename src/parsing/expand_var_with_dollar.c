#include "../../includes/minishell.h"

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

static char	*extract_env_variable_line(char *var_to_look_for, char **env_arr)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(var_to_look_for);
	while (env_arr[i] != NULL)
	{
		if (ft_strncmp(var_to_look_for, env_arr[i], j) == 0 && env_arr[i][j] == '=')
			break ;
		i++;
	}
	if (env_arr[i] == NULL)
	{
		free(var_to_look_for);
		var_to_look_for = NULL;
		return (NULL);
	}
	free(var_to_look_for);
	var_to_look_for = NULL;
	return (env_arr[i]);
}

static char	*get_var_to_look_for(char *content)
{
	char	*var;
	int		j;

	j = 0;
	while (content[j] != ' ' && content[j] != '\"'
		&& content[j] != '$' && content[j] != '\0'
		&& content[j] != '\'')
		j++;
	var = ft_calloc(sizeof(char), j + 1);
	if (var == NULL)
		return (NULL);
	ft_strncpy(var, content, j);
	return (var);
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
	char	*var_to_look_for;
	char	*env_var;
	int		i;

	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$' && what_is_dollar_in(content, i) == 0)
		{
			var_to_look_for = get_var_to_look_for(content + i + 1);
			if (!var_to_look_for)
			{
				free(content);
				return (NULL);
			}
			env_var = extract_env_variable_line(var_to_look_for, env_arr);
			content = manage_dollar(env_var, content, i);
			if (!content)
				return (NULL);
		}
		if (content[i])
			i++;
	}
	return (content);
}
