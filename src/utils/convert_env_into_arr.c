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
	ft_printf("count = %d\n", count);
	return (count);
}

char	**convert_env_into_arr(t_env_ms *env)
{
	char	**arr;
	int		len_ll;
	int		len_key_value_equal;
	int		i;

	len_ll = get_len_ll(env);
	arr = malloc(sizeof(char *) * (len_ll + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		len_key_value_equal = ft_strlen(env->key) + ft_strlen(env->value) + 1;
		arr[i] = malloc(sizeof(char) * (len_key_value_equal + 1));
		if (arr[i] == NULL)
		{
			free_double_arr(arr);
			return (NULL);
		}
		arr[i] = ft_strjoin(arr[i], env->key);
		arr[i] = ft_strjoin_free_first(arr[i], "=");
		arr[i] = ft_strjoin_free_first(arr[i], env->value);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
