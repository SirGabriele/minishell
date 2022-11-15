#include "../../includes/minishell.h"

/*static int	get_nb_cmd(t_cmd_list_ms *cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}*/

int	exec_pipex(t_pipeline_ms *pipeline)
{
	t_cmd_list_ms	*current_cmd;
	int				pipe_before[2];
	int				pipe_after[2];
	pid_t			child;
//	int				nb_cmd;

	if (pipe(pipe_before) == -1 || pipe(pipe_after) == -1)
		return (-1);
	child = fork();
	if (child == -1)
		return (-1);
//	nb_cmd = get_nb_cmd(pipeline->first_cmd);
	current_cmd = pipeline->first_cmd;
	while (current_cmd != NULL)
	{
		if (current_cmd == pipeline->first_cmd && child == 0)
			ft_printf("One\n");
		else if (current_cmd->next == NULL && child == 0)
			ft_printf("Last\n");
		else if (child == 0)
			ft_printf("Middle\n");
		current_cmd = current_cmd->next;
	}
	if (child == 0)
		exit(0);
	waitpid(child, NULL, WUNTRACED);//A RAJOUTER &STATUS
	return (0);
}
