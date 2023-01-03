#include "../../includes/minishell.h"

static void	free_memory_fork(t_pipes_ms *pipes, char **env_arr, t_env_ms *env_ll)
{
	free_binary_tree(pipes->tree_root);
	free_env_list(env_ll);
	free(pipes->children->pid_arr);
	free(pipes->children);
	free_double_arr(env_arr);
	free(pipes);
	close(0);
	close(1);
	close(2);
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

//free memory in forks
static void	go_in_child_process(t_pipes_ms *pipes, t_node_ms *node, t_env_ms *env_ll)
{
	char	**env_arr;
	char	*correct_path;

	env_arr = convert_env_ll_into_arr(env_ll);
	redirect_infile(pipes->before, node);
	redirect_outfile(pipes->after, node);
	if (env_arr == NULL || node->content == NULL)//a tester avec "> cat"
	{
		ft_putstr_fd("No command written\n", 2);//A VIRER
		free_memory_fork(pipes, env_arr, env_ll);
		exit(0);
	}
	correct_path = verify_cmd_path(node->content[0], env_arr);//obtenir le bon exit_code avec une fonction comme a la ligne 59
	if (correct_path == NULL)
	{
		free_memory_fork(pipes, env_arr, env_ll);
		ft_putstr_fd("Command does not exist\n", 2);//A VIRER
		exit(127);
	}
	execve(correct_path, node->content, env_arr);
	ft_putstr_fd("Execve failed\n", 2);//A VIRER
	free_memory_fork(pipes, env_arr, env_ll);
	exit(1);
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

//ajouter handle_all_redirs dans les builtin
int	execute_cmd(t_pipes_ms *pipes, t_children_ms *children, t_node_ms *node, t_env_ms **env_ll)//ajouter la separation si builtin ou non
{
	int	exit_code;

	exit_code = handle_all_redirs(node, pipes, *env_ll);
	if (exit_code != 0)
	{
		children->index++;
		return (-1);
	}
	if (is_cd_or_exit(node->content[0]) == 0 && node->shell == TOK_SHELL)//split simple commande et commande dans une pipeline. if pipeline ->exec dans un fork////is_a_simple_buitlin
		simple_cd_or_exit(node->content, *env_ll);
	else
	{
		children->pid_arr[children->index] = fork();
		if (children->pid_arr[children->index] == -1)
		{
			ft_putstr_fd("Fork() failed\n", 2);
			return (-1);
		}
		if (children->pid_arr[children->index] == 0)
			go_in_child_process(pipes, node, *env_ll);
	}
	children->index++;
	return (0);
}
