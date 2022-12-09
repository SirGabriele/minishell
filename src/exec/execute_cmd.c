#include "../../includes/minishell.h"

static void	redirect_outfile(int *pipe_after, t_node_ms *root)
{
	int	fd;

	if (root->outfile != NULL)
	{
		if (root->outfile_mode == TOK_TRUNC)
			fd = open(root->outfile, O_WRONLY | O_TRUNC);
		if (root->outfile_mode == TOK_APPEND)
			fd = open(root->outfile, O_WRONLY | O_APPEND);
		dup2(fd, 1);
		close(fd);
	}
	else
		dup2(pipe_after[1], 1);
	close(pipe_after[1]);
	close(pipe_after[0]);
}

static void	redirect_infile(int *pipe_before, t_node_ms *root)
{
	int	fd;

	if (root->infile != NULL && root->infile_mode == TOK_INFILE)
	{
		fd = open(root->infile, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("Could not open the specified infile\n", 2);
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
	else
		dup2(pipe_before[0], 0);
	close(pipe_before[0]);
	close(pipe_before[1]);
}

//free memory in forks
static void	go_to_fork(t_pipe_ms *pipes, t_node_ms *root, char **env)
{
	redirect_infile(pipes->before, root);
	redirect_outfile(pipes->after, root);
	execve(root->content[0], root->content, env);
	ft_printf("Execve failed\n");
	exit(1);
}

int	execute_cmd(t_pipe_ms *pipes, pid_t child, t_node_ms *root, char **env)
{
	child = fork();
	if (child == -1)
	{
		ft_putstr_fd("Forking failed\n", 2);
		return (-1);
	}
	if (child == 0)
		go_to_fork(pipes, root, env);
	return (0);
}
