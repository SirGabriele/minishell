#include "../../includes/minishell.h"

static int	examine_dollar_conditions(char *content, int i)
{
	if (content[i + 1] == ' ')
		return (1);
	if (content[i + 1] == '$')
		return (1);
	if (content[i + 1] == '\0')
		return (1);
	if (i > 0 && content[i - 1] == '\"' && content[i + 1] == '\"')
		return (1);
	if (ft_isdigit(content[i + 1]))
		return (2);
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
	tmp = ft_calloc(sizeof(char), i + 1);
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
	tmp = ft_calloc(sizeof(char), i + 1);
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
	{
		free(content);
		return (NULL);
	}
	tmp = ft_strjoin_free_first(tmp2, content + i + j + 1);
	free(content);
	return (tmp);
}

static char	*replace_argument(char *content, int i)
{
	char	*tmp;

	tmp = malloc((i + 1) * sizeof(char));
	if (!tmp)
	{
		free(content);
		return (NULL);
	}
	ft_strncpy(tmp, content, i);
	if (content[i + 1] == '0')
	{
		tmp = ft_strjoin_free_first(tmp, "minishell");
		if (!tmp)
		{
			free(content);
			return (NULL);
		}
	}
	tmp = ft_strjoin_free_first(tmp, content + i + 2);
	free(content);
	content = NULL;
	return (tmp);
}

char	*manage_dollar(char *env_var, char *content, int i)
{
	if (env_var)
		content = replace_dollar_by_env_var(content, env_var, i);
	else if (!examine_dollar_conditions(content, i))
		content = delete_dollar_from_line_if_needed(content, i);
	else if (examine_dollar_conditions(content, i) == 2)
		content = replace_argument(content, i);
	return (content);
}
