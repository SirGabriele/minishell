#include "../../includes/minishell.h"

/****************************************************************/
/*																*/
/*	Converts the double array containing all the environment	*/
/*		variables into a linked list							*/
/*																*/
/*	Parameters:													*/
/*		env	-	the double array containing all env variables	*/
/*																*/
/*	Return:														*/
/*		first_link	-	the first link of the list				*/
/*		NULL		-	malloc failed							*/
/*																*/
/****************************************************************/

t_env_ms	*convert_env_arr_into_ll(const char **env)
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
	return (first_link);
	cursor->next = ft_lstnew_env_entry("?=0");//A virer
}
