#include "../../includes/minishell.h"

static int	check_key_format(char *content)
{
	if (!ft_isalpha(content[0]) && content[0] != '_')
	{
		ft_printf_fd(2, "minishell: export: `%s': not a valid indentifier\n",
			content);
		return (1);
	}
	return (0);
}

static int	check_spaces_after_key(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=' && ft_isspace(content[i - 1]))
		{
			ft_printf_fd(2, "minishell: export: `%s': not a valid indentifier\n",
				content + i);
			return (1);
		}
		else if (content[i] == '=' && !ft_isspace(content[i - 1]))
			return (0);
		i++;
	}
	return (0);
}

int	check_errors_env_format(char **content)
{
	int		i;

	i = 0;
	while (content[i])
	{
		if (check_key_format(content[i]))
			return (1);
		else if (check_spaces_after_key(content[i]))
			return (1);
		i++;
	}
	return (0);
}
