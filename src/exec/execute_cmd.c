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
	if (root->outfile == NULL && root->outfile_mode == TOK_PIPE)
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
	if ((root->infile == NULL && root->infile_mode == TOK_PIPE)
			|| (root->infile != NULL && root->infile_mode == TOK_HEREDOC))
		dup2(pipe_before[0], 0);
	close(pipe_before[0]);
	close(pipe_before[1]);
}

//free memory in forks
static void	go_to_fork(t_pipe_ms *pipes, t_node_ms *root, char **env)
{
	int	marker;
	int	exit_code;

	marker = 0;
	exit_code = handle_all_redirs(root, pipes->before, &marker);
	if (exit_code != 0)
	{
		//free memory
		close(pipes->before[0]);
		close(pipes->before[1]);
		close(pipes->after[0]);
		close(pipes->after[1]);
		exit(exit_code);
	}
	redirect_infile(pipes->before, root);
	redirect_outfile(pipes->after, root);
	root->content[0] = verify_cmd_path(root, env);
	if (root->content[0] == NULL)
	{
		//free_memory
		ft_putstr_fd("Command does not exist\n", 2);//A VIRER;
		exit(127);
	}
//	ft_putstr_fd("Command exists\n", 2);//A VIRER
	execve(root->content[0], root->content, env);
//	ft_putstr_fd("Execve failed\n", 2);//A VIRER
	//free_memory
	exit(1);
}

//ajouter la separation si builtin ou non
int	execute_cmd(t_pipe_ms *pipes, t_children_ms *children, t_node_ms *root, char **env)
{
	children->pid_arr[children->index] = fork();
	if (children->pid_arr[children->index] == -1)
	{
		ft_putstr_fd("Forking failed\n", 2);
		return (-1);
	}
	if (children->pid_arr[children->index] == 0)
		go_to_fork(pipes, root, env);
	children->index++;
	return (0);
}
