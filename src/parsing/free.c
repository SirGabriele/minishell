#include "../../includes/minishell.h"

void	free_tokens(t_token_ms *tokens)
{
	t_token_ms	*tokens_cpy;

	while (tokens)
	{
		free(tokens->content);
		tokens->content = NULL;
		tokens_cpy = tokens->next;
		free(tokens);
		tokens = tokens_cpy;
	}
}

void	free_splited_tokens(t_token_ms **splited_tokens)
{
	free_tokens(splited_tokens[0]);
	free_tokens(splited_tokens[1]);
	free(splited_tokens);
	splited_tokens[0] = NULL;
	splited_tokens[1] = NULL;
	splited_tokens = NULL;
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

void	free_binary_tree(t_node_ms *binary_tree)
{
	if (binary_tree)
	{
		free(binary_tree->content);
		binary_tree->content = NULL;
		free_redirs_list(binary_tree->first_redir);
		binary_tree->first_redir = NULL;
		free(binary_tree->infile);
		binary_tree->infile = NULL;
		free(binary_tree->outfile);
		binary_tree->outfile = NULL;
		free_binary_tree(binary_tree->left);
		free_binary_tree(binary_tree->right);
	}
}
