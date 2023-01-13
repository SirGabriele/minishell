#include "../../includes/minishell.h"

static void	free_memory_fork_and_exit(t_pipes_ms *pipes, char **env_arr,
	t_env_ms *env_ll, int exit_code)
{
	free_binary_tree(pipes->tree_root);
	free_env_list(env_ll);
	free(pipes->children->pid_arr);
	free(pipes->children);
	if (env_arr != NULL)
		free_double_arr(env_arr);
	free(pipes);
	close(0);
	close(1);
	close(2);
	exit(exit_code);
}

static void	redirect_outfile(int *pipe_after, t_node_ms *node)
{
	int	fd;

	if (node->outfile != NULL)
	{
		if (node->outfile_mode == TOK_TRUNC)
			fd = open(node->outfile, O_WRONLY | O_TRUNC);
		if (node->outfile_mode == TOK_APPEND)
			fd = open(node->outfile, O_WRONLY | O_APPEND);
		dup2(fd, 1);
		close(fd);
	}
	if (node->outfile == NULL && node->outfile_mode == TOK_PIPE)
		dup2(pipe_after[1], 1);
	close(pipe_after[1]);
	close(pipe_after[0]);
}

static void	redirect_infile(int *pipe_before, t_node_ms *node)
{
	int	fd;

	if (node->infile != NULL && node->infile_mode == TOK_INFILE)
	{
		fd = open(node->infile, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	if ((node->infile == NULL && node->infile_mode == TOK_PIPE)
			|| (node->infile != NULL && node->infile_mode == TOK_HEREDOC))
		dup2(pipe_before[0], 0);
	close(pipe_before[0]);
	close(pipe_before[1]);
}

static void	go_in_child_process(t_pipes_ms *pipes,
	t_node_ms *node, t_env_ms *env_ll, int exit_code_redirs)
{
	char	**env_arr;
	char	*correct_path;
	int		exit_code;

	env_arr = convert_env_ll_into_arr(env_ll);
	redirect_infile(pipes->before, node);
	redirect_outfile(pipes->after, node);
	if (exit_code_redirs != 0)
		free_memory_fork_and_exit(pipes, env_arr, env_ll, exit_code_redirs);
	if (env_arr == NULL || node->content == NULL || node->content[0][0] == '\0')
		free_memory_fork_and_exit(pipes, env_arr, env_ll, 0);
	if (is_a_builtin(node->content[0]) == 0)
	{
		exit_code = exec_builtin(node, &env_ll, pipes, exit_code_redirs);
		free_memory_fork_and_exit(pipes, env_arr, env_ll, exit_code);
	}
	if (is_a_directory(node->content[0]) == 0 || is_permission_denied(node->content[0]) == 0)
		free_memory_fork_and_exit(pipes, env_arr, env_ll, 126);
	correct_path = verify_cmd_path(node->content[0], env_arr);
	if (correct_path == NULL)
		free_memory_fork_and_exit(pipes, env_arr, env_ll, 127);
	execve(correct_path, node->content, env_arr);
	free_memory_fork_and_exit(pipes, env_arr, env_ll, 2);//1 ou 2 a voir. Test où execve fail: .
}

/****************************************************************/
/*																*/
/*	Creates the child process in which the command will be		*/
/*		executed												*/
/*																*/
/*	Parameters:													*/
/*		pipes		-	structure containing the two pipes		*/
/*		children	-	structure containing the fork-linked	*/
/*						variables								*/
/*		node		-	node to process							*/
/*		env_ll		-	linked list of the env_variables		*/
/*																*/
/*	Return:														*/
/*		 0	-	accomplished its duty							*/
/*		-1	-	something failed								*/
/*																*/
/****************************************************************/

int	execute_cmd(t_pipes_ms *pipes, t_children_ms *children, t_node_ms *node, t_env_ms **env_ll)
{
	int	exit_code_redirs;

	exit_code_redirs = handle_all_redirs(node, pipes, *env_ll);
	if (node->content && is_a_builtin(node->content[0]) == 0 && node->shell == TOK_SHELL)
		children->pid_arr[children->index] = exec_builtin(node, env_ll, pipes, exit_code_redirs);
	else
	{
		children->pid_arr[children->index] = fork();
		if (children->pid_arr[children->index] == -1)
		{
			ft_putstr_fd("Fork() failed\n", 2);
			return (-1);
		}
		if (children->pid_arr[children->index] == 0)
			go_in_child_process(pipes, node, *env_ll, exit_code_redirs);
	}
	pipes->last_cmd_executed = children->index;
	children->index++;
	return (0);
}
