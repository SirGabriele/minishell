#include "../../includes/minishell.h"

static int	get_len_ll(t_env_ms *env)
{
	int	count;

	count = 0;
	while (env != NULL)
	{
		count++;
		env = env->next;
	}
//	ft_printf("count = %d\n", count);
	return (count);
}

char	*associate_key_value(t_env_ms *env)
{
	char	*str;

	str = NULL;
	str = ft_strjoin(str, env->key);
	str = ft_strjoin_free_first(str, "=");
	str = ft_strjoin_free_first(str, env->value);
	return (str);
}

char	**convert_env_into_arr(t_env_ms *env)
{
	char	**arr;
	int		len_ll;
	int		i;

	len_ll = get_len_ll(env);
	arr = malloc(sizeof(char *) * (len_ll + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		arr[i] = associate_key_value(env);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
