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

	if (root->infile != NULL && ft_strncmp(root->infile, "EOF", 4) != 0)
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
	close(0);
}

//free memory in forks
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
	waitpid(child, NULL, WUNTRACED);
/*	ft_printf("Content of pipe_before : |");
	print_pipe(pipe_before);
	ft_printf("|\n");
	ft_printf("Content of pipe_after : |");
	print_pipe(pipe_after);
	ft_printf("|\n");*/
	return (0);
}
