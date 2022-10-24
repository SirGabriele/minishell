#include "../../minishell.h"

int	len_arg_without_quotes(char *arg)
{
	int	i;
	int	i_cpy;
	int	len;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			i_cpy = i;
			i++;
			while (arg[i] && arg[i] != arg[i_cpy])
			{
				i++;
				len++;
			}
			i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*remove_arg_useless_quotes(char *arg)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(len_arg_without_quotes(arg) * sizeof(char));
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && what_is_character_in(arg, i))
		{
			tmp[j] = arg[i];
			j++;
			i++;
		}
		else
		{
			tmp[j] = arg[i];
			j++;
			i++;
		}
	}
	return (tmp);
}
