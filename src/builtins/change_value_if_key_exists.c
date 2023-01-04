#include "../../includes/minishell.h"

static int	get_delim_symbol_index(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=' || content[i] == '+')
			return (i);
		i++;
	}
	return (i);
}

static t_env_ms	*modify_value(char *content, t_env_ms *link_to_modify)
{
	free(link_to_modify->value);
	link_to_modify->value = ft_strdup(content);
	if (!link_to_modify->value)
	{
		perror(NULL);
		return (NULL);
	}
	return (link_to_modify);
}

static t_env_ms	*append_value(char *content, t_env_ms *link_to_modify)
{
	link_to_modify->value = ft_strjoin_free_first(link_to_modify->value, content);
	if (!link_to_modify->value)
	{
		perror(NULL);
		return (NULL);
	}
	return (link_to_modify);
}

static t_env_ms	*get_new_value_if_needed(char *content, t_env_ms *link_to_modify)
{
	int	index_equals_or_plus;

	index_equals_or_plus = get_delim_symbol_index(content);
	if (!ft_strncmp(link_to_modify->key, content, index_equals_or_plus))
	{
		if (content[index_equals_or_plus] == '+')
			link_to_modify = append_value(content + index_equals_or_plus + 2, link_to_modify);
		else if (content[index_equals_or_plus] == '=')
			link_to_modify = modify_value(content + index_equals_or_plus + 1, link_to_modify);
	}
	return (link_to_modify);
}

t_env_ms	*change_value(char *content, t_env_ms *link_to_modify)
{
/*	t_env_ms	*tmp_env;

	tmp_env = env_ll;
	while (env_ll)
	{
		env_ll = get_new_value_if_needed(content, env_ll);
		if (!env_ll)
		{
			free_env_list(tmp_env);
			perror(NULL);
			return (NULL);
		}
		env_ll = env_ll->next;
	}*/
	link_to_modify = get_new_value_if_needed(content, link_to_modify);
	return (link_to_modify);
}
