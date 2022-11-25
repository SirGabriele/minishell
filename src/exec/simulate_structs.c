#include "../../includes/minishell.h"

static void set_root_left_right_values(t_node_ms *node)
{
	node->content = malloc(sizeof(char *) * 3);
	node->content[0] = ft_strdup("cat");
	node->content[1] = ft_strdup("-e");
	node->content[2] = NULL;
	node->first_redir = malloc(sizeof(t_redir_ms));
	node->first_redir->file_name = ft_strdup("outfile");
	node->first_redir->mode = TOK_INFILE;
	node->first_redir->next = malloc(sizeof(t_redir_ms));
	node->first_redir->next->file_name = ft_strdup("outfile1");
	node->first_redir->next->mode = TOK_TRUNC;
	node->first_redir->next->next = malloc(sizeof(t_redir_ms));
	node->first_redir->next->next->file_name = ft_strdup("outfile2");
	node->first_redir->next->next->mode = TOK_APPEND;
	node->infile = ft_strdup("outfile");
	node->outfile = ft_strdup("outfile2");
	node->infile_mode = TOK_INFILE;
	node->outfile_mode = TOK_APPEND;
	node->operator = TOK_NULL;
}

static void set_root_left_left_values(t_node_ms *node)
{
	node->content = malloc(sizeof(char *) * 2);
	node->content[0] = ft_strdup("echo");
	node->content[1] = NULL;
	node->first_redir = malloc(sizeof(t_redir_ms));
	node->first_redir->file_name = ft_strdup("EOF");
	node->first_redir->mode = TOK_HEREDOC;
	node->first_redir->next = malloc(sizeof(t_redir_ms));
	node->first_redir->next->file_name = ft_strdup("infile");
	node->first_redir->next->mode = TOK_INFILE;
	node->first_redir->next->next = malloc(sizeof(t_redir_ms));
	node->first_redir->next->next->file_name = ft_strdup("outfile");
	node->first_redir->next->next->mode = TOK_APPEND;
	node->infile = ft_strdup("infile");
	node->outfile = ft_strdup("outfile");
	node->infile_mode = TOK_INFILE;
	node->outfile_mode = TOK_APPEND;
	node->operator = TOK_NULL;
}

static void set_root_right_values(t_node_ms *node)
{
	node->content = malloc(sizeof(char *) * 3);
	node->content[0] = ft_strdup("echo");
	node->content[1] = ft_strdup("fin");
	node->content[2] = NULL;
	node->first_redir = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_NULL;
	node->outfile_mode = TOK_NULL;
	node->operator = TOK_NULL;
}

static void set_root_left_values(t_node_ms *node)
{
	node->operator = TOK_PIPE;
}

static void	set_root_values(t_node_ms *root)
{
	root->operator = TOK_AND_OPER;
}

int	simulate_structs(t_node_ms *root, t_env_ms *env)
{
	set_root_values(root);
	root->left = malloc(sizeof(t_node_ms));
	init_root_struct(root->left);
	set_root_left_values(root->left);
	
	root->right = malloc(sizeof(t_node_ms));
	init_root_struct(root->right);
	set_root_right_values(root->right);
	
	root->left->left = malloc(sizeof(t_node_ms));
	init_root_struct(root->left->left);
	set_root_left_left_values(root->left->left);
	
	root->left->right = malloc(sizeof(t_node_ms));
	init_root_struct(root->left->right);
	set_root_left_right_values(root->left->right);
	
	print_tree(root);
	if (launch_exec(root, env) == -1)
		return (-1);
	return (0);
}
