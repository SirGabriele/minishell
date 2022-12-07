#include "../../includes/minishell.h"

static int	transfer_pipe_content(int *pipe_before, int *pipe_after)
{
	close(pipe_before[0]);
	close(pipe_before[1]);
	pipe_before[0] = dup(pipe_after[0]);
	pipe_before[1] = dup(pipe_after[1]);
	close(pipe_after[0]);
	close(pipe_after[1]);
	if (pipe(pipe_after) == -1)
	{
		ft_putstr_fd("Pipe_after's creation failed\n", 2);
		return (-1);
	}
	return (0);
}

static int	process_node(t_node_ms *root, t_env_ms *env,
	int *pipe_before, int *pipe_after)
{
	char	**env_arr;
	int		ret;

	ret = 0;
	if (root->operator == TOK_PIPE || root->operator == TOK_AND_OPER || root->operator == TOK_OR_OPER)
		return (0);
/*	if (root->operator == TOK_AND_OPER && ret == 0)
		execute command*/
/*	if (root->operator == TOK_OR_OPER && ret != 0)
		execute command*/
	if (handle_all_redirs(root, pipe_before) == -1)
		return (-1);
	/*separer si builtin ou non*/
	env_arr = convert_env_into_arr(env);
	if (env_arr == NULL)
		return (-1);
	ret = execute_cmd(root, pipe_before, pipe_after, env_arr);
	if (ret == -1)
		return (-1);
	if (transfer_pipe_content(pipe_before, pipe_after) == -1)
		return (-1);
	/*if (root->infile == NULL)
		use_pipe_as_infile();*/
	/*if (root->operator == TOK_PIPE)*/
		/*send_pipe_left_to_right(root);*/
	/*gerer infile*/
	/*gerer outfile*/
	/*if TOK_SHELL -> is not in parenthesis*/
	/*if != TOK_SHELL -> is in parenthesis*/
	/*recuperer &status*/
	return (ret);
}

//Ajouter les valeurs de retours des waitpids
int	launch_exec(t_node_ms *root, t_env_ms *env)
{
	int	pipe_before[2];
	int	pipe_after[2];

	if (pipe(pipe_before) == -1 || pipe(pipe_after) == -1)
		return (-1);
	if (root->left != NULL)
		launch_exec(root->left, env);
	if (process_node(root, env, pipe_before, pipe_after) == -1)
		return (-1);
	/*trouver moyen de confirmer/infirmer le fait d'aller dans right vis à vis de && et ||*/
	if (root->right != NULL)
		launch_exec(root->right, env);
	if (pipe_before[0] != 0)
		close(pipe_before[0]);
	if (pipe_before[1] != 0)
		close(pipe_before[1]);
/*	if (pipe_after[0] != 0)
		close(pipe_after[0]);
	if (pipe_after[1] != 0)
		close(pipe_after[1]);*/
	return (0);
}
