#include "../../includes/minishell.h"

void	set_exit_code(t_env_ms *env_ll, int exit_code)
{
	t_env_ms	*cursor;

	cursor = env_ll;
	while (cursor != NULL)
	{
		if (ft_strncmp(cursor->key, "?", 1) == 0)
		{
			free(cursor->value);
			cursor->value = ft_itoa(exit_code);
		}
		cursor = cursor->next;
	}
}

void	get_exit_code(t_env_ms *env_ll)
{
	t_env_ms	*cursor;

	cursor = env_ll;
	while (cursor != NULL)
	{
		if (ft_strncmp(cursor->key, "?", 1) == 0)
			ft_printf_fd(1, "%s\n", cursor->value);
		cursor = cursor->next;
	}
}
