#include "../../includes/minishell.h"

char	*get_key_value(t_env_ms *env_ll, char *key)
{
	char	*value;
	int		len;

	value = NULL;
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
