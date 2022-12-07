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
	close(1);
}

static void	redirect_infile(int *pipe_before, t_node_ms *root)
{
	int	fd;

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
}

static void	go_to_fork(int *pipe_before, int *pipe_after, t_node_ms *root, char **env)
{
	close(pipe_before[1]);
	close(pipe_after[0]);
	redirect_infile(pipe_before, root);
	redirect_outfile(pipe_after, root);
	close(2);
	ft_printf("Execve next line\n");
	execve(root->content[0], root->content, env);
	ft_printf("Execve failed\n");
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
	ft_printf("Hello from the child\n");
	exit(0);
}

int	execute_cmd(int *pipe_before, int *pipe_after, t_node_ms *root, char **env)
{
	pid_t	child;

	child = fork();
	if (child == -1)
	{
		ft_putstr_fd("Forking failed\n", 2);
		return (-1);
	}
	if (child == 0)
		go_to_fork(pipe_before, pipe_after, root, env);
	ft_printf("---------------\nContent of pipe_before : ");
//	print_pipe(pipe_before, env);
	ft_printf("\n");
	ft_printf("Content of pipe_after : ");
	print_pipe(pipe_after, env);
	ft_printf("\n---------------\n");
	waitpid(child, NULL, WUNTRACED);
	return (0);
}
