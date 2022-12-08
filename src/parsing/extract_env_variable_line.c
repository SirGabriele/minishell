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
char	*extract_env_variable_line(char *var_to_look_for, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(var_to_look_for);
	while (env[i] != NULL)
	{
		if (ft_strncmp(var_to_look_for, env[i], j) == 0 && env[i][j] == '=')
			break ;
		i++;
	}
	if (env[i] == NULL)
	{
		free(var_to_look_for);
		var_to_look_for = NULL;
		return (NULL);
	}
	free(var_to_look_for);
	var_to_look_for = NULL;
	return (env[i]);
}

char	*get_var_to_look_for(char *content)
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
