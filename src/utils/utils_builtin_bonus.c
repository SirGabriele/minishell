#include "../../includes/minishell.h"

static int	is_smaller_than_llong_min(char *content)
{
	int	res;

	res = ft_strcmp(content, "9223372036854775808");
	if (res > 0)
		return (1);
	return (0);
}

static int	is_bigger_than_llong_max(char *content)
{
	int	res;

	res = ft_strcmp(content, "9223372036854775808");
	if (res >= 0)
		return (1);
	return (0);
}

int	is_value_out_of_range(char *content)
{
	int	len_content;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	while (ft_isspace(content[i]) == 1)
		i++;
	if (content[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (content[i] == '+')
		i++;
	len_content = ft_strlen(content + i);
	if (len_content < 19)
		return (0);
	else if (len_content > 19)
		return (1);
	if ((sign == 1 && is_bigger_than_llong_max(content + i) == 1)
		|| (sign == -1 && is_smaller_than_llong_min(content + i) == 1))
		return (1);
//	else if (sign == -1 && is_smaller_than_llong_min(content + i) == 1)
//		return (1);
	return (0);
}

int	count_args(char **content)
{
	int	i;

	i = 0;
	while (content[i])
		i++;
	return (i);
}

void	sort_env_ll(t_env_ms *env_ll)
{
	t_env_ms	*current;
	t_env_ms	*next;
	char		*temp_key;
	char		*temp_value;

	current = env_ll;
	while (current->next != NULL)
	{
		next = current->next;
		if (ft_strcmp(current->key, next->key) > 0)
		{
			temp_key = next->key;
			temp_value = next->value;
			next->key = current->key;
			next->value = current->value;
			current->key = temp_key;
			current->value = temp_value;
			current = env_ll;
		}
		else
		{
			current = current->next;
			next = current->next;
		}
	}
}
