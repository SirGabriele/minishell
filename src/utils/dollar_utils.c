#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*  Determines if the environment variable found is between			*/
/*	single/double quotes or not in any sort of quotes				*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		parsed	-	line from the terminal							*/
/*		i		-	index of the '$' symbol found					*/
/*																	*/
/*  Return:															*/
/*		0	-	env_variable is between double quotes or alone		*/
/*		1	-	env_variable is between single quotes				*/
/*																	*/
/********************************************************************/

int	what_is_dollar_in(const char *parsed, int i)
{
	int		j;
	char	c;

	j = 0;
	while (parsed[j] != '\0')
	{
		if (parsed[j] == '\"' || parsed[j] == '\'')
		{
			c = parsed[j];
			j++;
			while (parsed[j] != c && parsed[j] != '\0')
				j++;
			if (j > i && c == '\"')
				return (0);
			else if (j > i && c == '\'')
				return (-1);
		}
		else if (parsed[j] == '$')
			return (0);
		j++;
	}
	return (-1);
}

int	count_dollars_to_replace(char *content)
{
	int	i;
	int	nb_dollars;

	i = 0;
	nb_dollars = 0;
	while (content[i])
	{
		if (content[i] == '$' && !what_is_dollar_in(content, i))
			nb_dollars++;
		i++;
	}
	return (nb_dollars);
}

char	*get_key_to_expand(char *parsed)
{
	char	*key_to_expand;
	int		j;

	j = 0;
	while (parsed[j] != ' ' && parsed[j] != '\"'
		&& parsed[j] != '$' && parsed[j] != '\0'
		&& parsed[j] != '\'' && parsed[j] != '=')
		j++;
	key_to_expand = ft_strndup(parsed, j);
	if (key_to_expand == NULL)
	{
		free(parsed);
		perror(NULL);
		return (NULL);
	}
	return (key_to_expand);
}

char	*get_key_value(t_env_ms *env_ll, char *key)
{
	int	len;

	len = ft_strlen(key);
	while (env_ll)
	{
		if (!ft_strncmp(env_ll->key, key, len) 
			&& len && !env_ll->key[len])
			return (env_ll->value);
		env_ll = env_ll->next;
	}
	return (NULL);
}
