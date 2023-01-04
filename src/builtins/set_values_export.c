#include "../../includes/minishell.h"

t_env_ms	*extend_env_list(char *content, t_env_ms *env_ll)
{
	t_env_ms	*tmp_env;

	tmp_env = env_ll;
	while (env_ll->next)
		env_ll = env_ll->next;
	env_ll->next = get_env(content);
	if (env_ll->next == NULL)
		return (NULL);
	return (tmp_env);
}

static t_env_ms *does_key_exist(char *content, t_env_ms *env_ll)
{
	int	len;

	while (env_ll)
	{
		len = ft_strlen(env_ll->key);
		if (!ft_strncmp(content, env_ll->key, len)
			&& (content[len] == '=' || content[len] == '+'
			|| !content[len]))
			return (env_ll);
		env_ll = env_ll->next;
	}
	return (NULL);
}

t_env_ms	*set_values_export(char *content, t_env_ms *env_ll)//export = casse $? && export =toto $?=toto
{
	t_env_ms	*link_to_modify;
	
	link_to_modify = does_key_exist(content, env_ll);
	if (link_to_modify != NULL)
		env_ll = change_value(content, link_to_modify);
	else
		env_ll = extend_env_list(content, env_ll);
	if (!env_ll)
	{
		perror(NULL);
		return (NULL);
	}
	else
		set_exit_code(env_ll, 0);
	return (env_ll);
}
