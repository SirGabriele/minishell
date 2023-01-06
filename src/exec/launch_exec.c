#include "../../includes/minishell.h"

static void	fill_to_wait_or_not_to_wait(int *to_wait_or_not_to_wait,
	t_node_ms *root, int *i)
{
	if (root->left != NULL)
		fill_to_wait_or_not_to_wait(to_wait_or_not_to_wait, root->left, i);
	if (is_operator(root->operator) == 0 && root->content)
	{
		if (root->content && is_a_builtin(root->content[0]) == 0 && root->shell == TOK_SHELL)
			to_wait_or_not_to_wait[*i] = 0;
		else
			to_wait_or_not_to_wait[*i] = 1;
		(*i)++;
	}
	if (root->right != NULL)
		fill_to_wait_or_not_to_wait(to_wait_or_not_to_wait, root->right, i);
}

static void	wait_for_all_the_forks(t_children_ms *children, t_env_ms *env_ll,
	int nb_nodes, t_node_ms *root)
{
	int	*to_wait_or_not_to_wait;
	int	i;
	int	wstatus;
	int	exit_code;

	i = 0;
	exit_code = 0;
	wstatus = 0;
	to_wait_or_not_to_wait = malloc(sizeof(int) * nb_nodes);
	fill_to_wait_or_not_to_wait(to_wait_or_not_to_wait, root, &i);
	i = 0;
	while (i < children->index)
	{
		if (to_wait_or_not_to_wait[i] == 1)
			waitpid(children->pid_arr[i], &wstatus, WUNTRACED);
		else
			exit_code = children->pid_arr[i];
		i++;
	}
	if (to_wait_or_not_to_wait[i - 1] == 1 && WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	set_exit_code(env_ll, exit_code);
	free(children->pid_arr);
	free(children);
	free(to_wait_or_not_to_wait);
}

static int	get_nb_nodes(t_node_ms *root, int *i)
{
	if (root->left != NULL)
		get_nb_nodes(root->left, i);
	if (root->left == NULL)
		(*i)++;
	if (root->right != NULL)
		get_nb_nodes(root->right, i);
	return (*i);
}

/****************************************************************/
/*																*/
/*	Carries out the whole execution process (preparation		*/
/*		execution, fork waiting)								*/
/*																*/
/*	Parameters:													*/
/*		root	-	root of the binary tree						*/
/*		env_ll	-	linked list containing the env variables	*/
/*																*/
/*	Return:														*/
/*		 0	-	accomplished its duty							*/
/*		-1	-	something failed								*/
/*																*/
/****************************************************************/

int	launch_exec(t_node_ms *root, t_env_ms *env_ll)
{
	t_children_ms	*children;
	t_pipes_ms		*pipes;
	int				nb_nodes;

	pipes = malloc(sizeof(t_pipes_ms));
	if (pipes == NULL)
		return (-1);
	if (pipe(pipes->before) == -1 || pipe(pipes->after) == -1)
		return (-1);
	nb_nodes = 0;
	nb_nodes = get_nb_nodes(root, &nb_nodes);
	children = NULL;
	children = initialize_children(children, nb_nodes);
	if (children == NULL)
		return (-1);
	pipes->tree_root = root;
	pipes->children = children;
	if (start_recursive(pipes, children, root, env_ll) == -1)
		return (-1);
	if (close(pipes->before[0]) == -1 || close(pipes->before[1]) == -1)
		return (-1);
	if (close(pipes->after[0]) == -1 || close(pipes->after[1]) == -1)
		return (-1);
	wait_for_all_the_forks(children, env_ll, nb_nodes, root);
	free(pipes);
	return (0);
}
