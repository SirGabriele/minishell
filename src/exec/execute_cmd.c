#include "../../includes/minishell.h"

static void	go_to_fork(t_node_ms *root, int *pipe_before, int *pipe_after, char **env)
{
	(void)root;
	(void)pipe_before;
	(void)pipe_after;
	(void)env;
/*	int	fd;

	close(pipe_after[0]);
	close(pipe_before[1]);
	if (root->infile != NULL)
	{
		fd = open(root->infile, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	else
		dup2(pipe_before[0], 0);
	close(pipe_before[0]);
	close(0);
	if (root->outfile != NULL)
	{
		fd = open(root->outfile, O_WRONLY | O_APPEND);
		dup2(fd, 1);
		close(fd);
	}
	else
		dup2(pipe_after[1], 1);
	close(pipe_after[1]);
	close(1);
	close(2);
	execve(root->content[0], root->content, env);*/
}

int	execute_cmd(t_node_ms *root, int *pipe_before, int *pipe_after, char **env)
{
	pid_t	child;

	child = fork();
	if (child == -1)
	{
		ft_putstr_fd("Forking failed\n", 2);
		return (-1);
	}
	if (child == 0)
		go_to_fork(root, pipe_before, pipe_after, env);
	waitpid(child, NULL, WUNTRACED);
	return (0);
}
