#include "../../includes/minishell.h"

t_env_ms	*convert_env_into_ll(const char **env)
{
	t_env_ms	*first_link;
	t_env_ms	*cursor;
	int			i;

	i = 0;
	first_link = ft_lstnew_env_entry(env[i]);
	if (first_link == NULL)
		return (NULL);
	cursor = first_link;
	i++;
	while (env[i] != NULL)
	{
		cursor->next = ft_lstnew_env_entry(env[i]);
		cursor = cursor->next;
		i++;
	}
	cursor->next = ft_lstnew_env_entry("toto=tata");//parasite
	cursor->next->next = ft_lstnew_env_entry("1=2");//parasite
	cursor->next->next->next = ft_lstnew_env_entry("2=3");//parasite
	cursor->next->next->next->next = ft_lstnew_env_entry("3=4");//parasite
	return (first_link);
}
