#include "../../includes/minishell.h"

t_redir_ms	*lstnew_redir(void)
{
	t_redir_ms	*lst;

	lst = malloc(sizeof(t_redir_ms));
	if (!lst)
		return (NULL);
	lst->file_name = NULL;
	lst->mode = TOK_NULL;
	lst->next = NULL;
	return (lst);
}

t_redir_ms	*get_redirections_list(t_token_ms *tokens)
{
	t_redir_ms	*first_redir;
	t_token_ms	*tmp_tok;

	first_redir = NULL;
	tmp_tok = tok;
	while (tmp_tok)
	{
		if (tmp_tok->type == TOK_INFILE || tmp_tok->type == TOK_TRUNC
			|| tmp_tok->type == TOK_HEREDOC || tmp_tok->type == TOK_APPEND)
			tmp_first_redir = get_infos(tmp_tok);
		tmp_tok = tmp_tok->next->next;
	}
	return (first_redir);
}

t_node_ms	*get_redirections_infos(t_token_ms *tokens)
{
	t_node_ms	*binary_tree;

	binary_tree = malloc(sizeof(t_node_ms));
	if (!binary_tree)
		return (NULL);
	binary_tree->first_redir = get_redirections_list(tokens);
}
