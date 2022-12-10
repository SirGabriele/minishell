#include "../../includes/minishell.h"

static int	get_nb_cmd(t_node_ms *root)
{
	static int	i = 0;

	if (root->left != NULL)
		get_nb_cmd(root->left);
	if (root->left == NULL)
		i++;
	if (root->right != NULL)
		get_nb_cmd(root->right);
	return (i);
}

/*static void	set_root_left_right_right_right_values(t_node_ms *node)
{
	node->content = malloc(sizeof(char *) * 3);
	node->content[0] = ft_strdup("/usr/bin/grep");
	node->content[1] = ft_strdup("fond");
	node->content[2] = NULL;
	node->first_redir = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_NULL;
	node->outfile_mode = TOK_NULL;
	node->operator = TOK_NULL;
}*/

/*static void	set_root_left_right_right_left_values(t_node_ms *node)
{
	node->content = malloc(sizeof(char *) * 3);
	node->content[0] = ft_strdup("/usr/bin/echo");
	node->content[1] = ft_strdup("fond");
	node->content[2] = NULL;
	node->first_redir = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_NULL;
	node->outfile_mode = TOK_NULL;
	node->operator = TOK_NULL;
}*/

/*static void	set_root_left_right_right_values(t_node_ms *node)
{
	node->operator = TOK_PIPE;
}*/

/*static void set_root_left_right_left_values(t_node_ms *node)
{
	node->content = malloc(sizeof(char *) * 3);
	node->content[0] = ft_strdup("/usr/bin/echo");
	node->content[1] = ft_strdup("coucou");
	node->content[2] = NULL;
	node->first_redir = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_NULL;
	node->outfile_mode = TOK_NULL;
	node->operator = TOK_NULL;
}*/

/*static void	set_root_left_right_values(t_node_ms *node)
{
	node->operator = TOK_PIPE;
}*/

/*static void	set_root_left_left_values(t_node_ms *node)
{
	node->content = malloc(sizeof(char *) * 3);
	node->content[0] = ft_strdup("/usr/bin/echo");
	node->content[1] = ft_strdup("test");
	node->content[2] = NULL;
	node->first_redir = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_NULL;
	node->outfile_mode = TOK_NULL;
	node->operator = TOK_NULL;
}*/

static void	set_root_right_values(t_node_ms *node)
{
	node->content = malloc(sizeof(char *) * 3);
	node->content[0] = ft_strdup("/usr/bin/ls");
	node->content[1] = NULL;
	node->first_redir = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_PIPE;
	node->outfile_mode = TOK_NULL;
	node->operator = TOK_NULL;
}

static void	set_root_left_values(t_node_ms *node)
{
	node->content = malloc(sizeof(char *) * 3);
	node->content[0] = ft_strdup("/usr/bin/catt");
	node->content[1] = NULL;
	node->first_redir = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_NULL;
	node->outfile_mode = TOK_PIPE;
	node->operator = TOK_NULL;
}

static void	set_root_values(t_node_ms *root)
{
	root->operator = TOK_PIPE;
}

int	simulate_structs(t_node_ms *root, t_env_ms *env)
{
	t_pipe_ms	*pipes;
	pid_t		*children_arr;
	int			nb_cmd;
	int			i;

	pipes = malloc(sizeof(t_pipe_ms));
	if (pipes == NULL)
		return (-1);
	if (pipe(pipes->before) == -1 || pipe(pipes->after) == -1)
		return (-1);
	set_root_values(root);
	root->left = malloc(sizeof(t_node_ms));
	init_root_struct(root->left);
	set_root_left_values(root->left);

	root->right = malloc(sizeof(t_node_ms));
	init_root_struct(root->right);
	set_root_right_values(root->right);

/*	root->left->left = malloc(sizeof(t_node_ms));
	init_root_struct(root->left->left);
	set_root_left_left_values(root->left->left);

	root->left->right = malloc(sizeof(t_node_ms));
	init_root_struct(root->left->right);
	set_root_left_right_values(root->left->right);
	
	root->left->right->left = malloc(sizeof(t_node_ms));
	init_root_struct(root->left->right->left);
	set_root_left_right_left_values(root->left->right->left);
	
	root->left->right->right = malloc(sizeof(t_node_ms));
	init_root_struct(root->left->right->right);
	set_root_left_right_right_values(root->left->right->right);
	
	root->left->right->right->left = malloc(sizeof(t_node_ms));
	init_root_struct(root->left->right->right->left);
	set_root_left_right_right_left_values(root->left->right->right->left);
	
	root->left->right->right->right = malloc(sizeof(t_node_ms));
	init_root_struct(root->left->right->right->right);
	set_root_left_right_right_right_values(root->left->right->right->right);*/

	print_tree(root); (void)env;
	i = 0;
	nb_cmd = get_nb_cmd(root);
	children_arr = malloc(sizeof(pid_t) * nb_cmd);
	if (children_arr == NULL)
		return (-1);
	if (start_recursive(pipes, children_arr, root, env) == -1)
		return (-1);
	if (close(pipes->before[0]) == -1)
		return (-1);
	if (close(pipes->before[1]) == -1)
		return (-1);
	while (i < nb_cmd)
	{
		waitpid(children_arr[i], NULL, WUNTRACED);
		i++;
	}
	return (0);
}
