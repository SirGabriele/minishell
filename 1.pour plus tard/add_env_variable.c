#include "../includes/minishell.h"

static int	add_last_string_and_null(char **arr, char *new_env_var, int i)
{
	arr[i] = ft_strdup(new_env_var);
	if (arr[i] == NULL)
	{
		free_double_arr(arr);
		return (-1);
	}
	arr[i + 1] = NULL;
	return (0);
}

static int	get_len_env_copy(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i] != NULL)
		i++;
	return (i);
}

char	**add_env_variable(char **env_copy, char *new_env_var)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (get_len_env_copy(env_copy) + 2));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (env_copy[i] != NULL)
	{
		arr[i] = ft_strdup(env_copy[i]);
		if (arr[i] == NULL)
		{
			free_double_arr(arr);
			return (NULL);
		}
		i++;
	}
	if (add_last_string_and_null(arr, new_env_var, i) == -1)
		free_double_arr(arr);
	free_double_arr(env_copy);
	return (arr);
}
