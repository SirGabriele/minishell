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

static char	*delete_dollar_from_line_if_needed(char *content, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = ft_strndup(content, i);
	i++;
	while (!ft_isspace(content[i + j]) && content[i + j] != '\"'
		&& content[i + j] != '$' && content[i + j] != '\0'
		&& content[i + j] != '\'' && !ft_isdigit(content[i + j - 1]))
		j++;
	if (tmp)
		tmp = ft_strjoin_free_first(tmp, content + i + j);
	free(content);
	return (tmp);
}

static char	*replace_dollar_by_env_var(char *content, char *env_var, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = ft_strndup(content, i);
	while (env_var[j] != '=' && env_var[j] != '\0')
		j++;
	if (tmp)
		tmp = ft_strjoin_free_first(tmp, env_var + j + 1);
	if (tmp)
		tmp = ft_strjoin_free_first(tmp, content + i + j + 1);
	free(content);
	return (tmp);
}

static char	*replace_dollar_digit(char *content, int i)
{
	char	*tmp;

	tmp = ft_strndup(content, i);
	if (content[i + 1] == '0' && tmp)
		tmp = ft_strjoin_free_first(tmp, "minishell");
	if (tmp)
		tmp = ft_strjoin_free_first(tmp, content + i + 2);
	free(content);
	return (tmp);
}

/****************************************************************/
/*                                                     			*/
/*  Replaces dollar by env variable								*/
/*                                                     	 		*/
/*  Parameters:													*/
/*		env_var	-	env variable line							*/
/*		content	-	string with dollar							*/
/*		i		-	dollar index								*/
/*																*/
/*  Return:														*/
/*		content	-	the newly formed line						*/
/*																*/
/****************************************************************/

char	*manage_dollar(char *env_var, char *content, int i)
{
	if (env_var)
		content = replace_dollar_by_env_var(content, env_var, i);
	else if (!examine_dollar_conditions(content, i))
		content = delete_dollar_from_line_if_needed(content, i);
	else if (examine_dollar_conditions(content, i) == 2)
		content = replace_dollar_digit(content, i);
	if (!content)
		perror(NULL);
	return (content);
}
