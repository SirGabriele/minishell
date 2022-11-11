#include "../../includes/minishell.h"

t_cmd_list_ms	*ft_lstnew_cmd(char *command_and_args)
{
	t_cmd_list_ms	*elem;

	elem = malloc(sizeof(t_cmd_list_ms));
	if (!elem)
		return (NULL);
	elem->command_and_args = ft_split(command_and_args, ' ');
	elem->next = NULL;
	return (elem);
}
