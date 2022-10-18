#include "../../includes/minishell.h"

static char	*add_space_at_this_index(char **user_input, int i)
{
	char	*new_user_input;
	char	*tmp;

	new_user_input = ft_calloc(sizeof(char), ft_strlen(*user_input) + 2);
	if (new_user_input == NULL)
		return (NULL);
	new_user_input = ft_strncpy(new_user_input, *user_input, i);
	tmp = ft_strjoin(new_user_input, " ");
	free(new_user_input);
	new_user_input = NULL;
	new_user_input = ft_strjoin(tmp, *user_input + i);
	free(tmp);
	free(*user_input);
	return (new_user_input);
}

static char	*add_space_before_operators_or_pipes(char **user_input)
{
	int	i;

	i = 0;
	while ((*user_input)[i] != '\0')
	{
		if ((((*user_input)[i] == '&' && (*user_input)[i + 1] == '&')
			|| ((*user_input)[i] == '|' && (*user_input)[i + 1] == '|'))
			&& (*user_input)[i - 1] != ' ')
		{
			*user_input = add_space_at_this_index(user_input, i);
			i += 2;
		}
		i++;
	}
	i = 0;
	while ((*user_input)[i] != '\0')
	{
		if ((*user_input)[i] == '|' && (*user_input)[i + 1] != '|'
			&& (*user_input)[i - 1] != ' ' && (*user_input)[i - 1] != '|')
		{
			*user_input = add_space_at_this_index(user_input, i);
			i++;
		}
		i++;
	}
	return (*user_input);
}

static char	*add_space_after_operators_or_pipes(char **user_input)
{
	int	i;

	i = 0;
	while ((*user_input)[i] != '\0')
	{
		if ((((*user_input)[i] == '&' && (*user_input)[i + 1] == '&')
			|| ((*user_input)[i] == '|' && (*user_input)[i + 1] == '|'))
			&& ((*user_input)[i + 2] != ' '))
		{
			*user_input = add_space_at_this_index(user_input, i + 2);
			if (*user_input == NULL)
				return (NULL);
			i += 2;
		}
		else if ((*user_input)[i] == '|' && (*user_input)[i + 1] != '|'
			&& ((*user_input)[i + 1] != ' '))
		{
			*user_input = add_space_at_this_index(user_input, i + 1);
			if (*user_input == NULL)
				return (NULL);
			i++;
		}
		i++;
	}
	return (*user_input);
}

char	*add_spaces_around_operators_and_pipes(char **user_input)
{
	*user_input = add_space_after_operators_or_pipes(user_input);
	*user_input = add_space_before_operators_or_pipes(user_input);
	return (*user_input);
}
