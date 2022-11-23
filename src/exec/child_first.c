#include "../../includes/minishell.h"

void	child_first(t_context_ms *context, int i)
{
	t_context_ms	*current;
	int	j;

	current = context;
	j = 0;
	ft_printf("In first_child\n");
	while (j < i)
	{
		curent = current->next;
		j++;
	}
	dup2()
}
