#include "../../includes/minishell.h"

void	free_n_tokens(t_token_ms *tokens, int nb_to_free)
{
	t_token_ms	*tokens_cpy;
	int			nb;

	if (!nb_to_free)
		nb = count_nb_of_tokens_left(tokens);
	else
		nb = nb_to_free;
	while (tokens && nb)
	{
		free(tokens->content);
		tokens->content = NULL;
		tokens_cpy = tokens->next;
		free(tokens);
		tokens = tokens_cpy;
		nb--;
	}
}

void	free_splited_tokens(t_token_ms **splited_tokens)
{
	free_n_tokens(splited_tokens[0], 0);
	free_n_tokens(splited_tokens[1], 0);
	free(splited_tokens);
}

void	free_redirs_list(t_redir_ms *first_redir)
{
	t_redir_ms *tmp_first_redir;

	while (first_redir)
	{
		free(first_redir->file_name);
		first_redir->file_name = NULL;
		tmp_first_redir = first_redir->next;
		free(first_redir);
		first_redir = tmp_first_redir;
	}
}

void	free_redirs_infos(t_node_ms *binary_tree)
{
		free(binary_tree->infile);
		free(binary_tree->outfile);
		binary_tree->infile = NULL;
		binary_tree->outfile = NULL;
}

static void	free_double(char **binary_tree_content)
{
	int	i;

	i = 0;
	if (binary_tree_content)
	{
		while (binary_tree_content[i])
		{
			free(binary_tree_content[i]);
			binary_tree_content[i] = NULL;
			i++;
		}
		free(binary_tree_content);
		binary_tree_content = NULL;
	}
}

void	free_binary_tree(t_node_ms *binary_tree)
{
	if (binary_tree)
	{
		free_double(binary_tree->content);
		free_redirs_list(binary_tree->first_redir);
		binary_tree->first_redir = NULL;
		free(binary_tree->infile);
		binary_tree->infile = NULL;
		free(binary_tree->outfile);
		binary_tree->outfile = NULL;
		free_binary_tree(binary_tree->left);
		free_binary_tree(binary_tree->right);
		free(binary_tree);
	}
}
