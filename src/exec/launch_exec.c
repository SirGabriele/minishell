#include "../../includes/minishell.h"

static void	wait_for_all_the_forks(t_children_ms *children, int nb_nodes, t_env_ms *env_ll)
{
	int	i;
	int	wstatus;
	int	exit_code;

	i = 0;
	while (i < nb_nodes)
	{
		waitpid(children->pid_arr[i], &wstatus, WUNTRACED);
		i++;
	}
	if (WIFEXITED(wstatus))
	{
		exit_code = WEXITSTATUS(wstatus);
		ft_printf_fd(2, "Exit code is : %d\n", exit_code);//A VIRER
		if (exit_code == 0)
			ft_putstr_fd("\e[42mSuccess\e[0m\n", 2);//A VIRER
		else
			ft_putstr_fd("\e[41mFailure\e[0m\n", 2);//A VIRER
	}
	(void)env_ll;
//	set_exit_code_to(env_ll, exit_code);
}

static int	get_nb_nodes(t_node_ms *root, int *i)//ne pas compter les nodes qui sont entre des () car ils iront dans des sous forks. If root->operator == TOK_OP_PAR -> ne pas incrémenter while root->operator == TOK_CL_PAR
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
	if (start_recursive(pipes, children, root, env_ll) == -1)
		return (-1);
	if (close(pipes->before[0]) == -1 || close(pipes->before[1]) == -1)
		return (-1);
	wait_for_all_the_forks(children, nb_nodes, env_ll);
	//free children
	return (0);
}
