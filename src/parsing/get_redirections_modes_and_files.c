#include "../../includes/minishell.h"

static int	is_last_outfile(t_redir_ms *first_redir)
{
	t_redir_ms *tmp_first_redir;

	tmp_first_redir = first_redir->next;
	while (tmp_first_redir)
	{
		if (tmp_first_redir->mode == TOK_TRUNC)
			return (0);
		else if (tmp_first_redir->mode == TOK_APPEND)
			return (0);
		tmp_first_redir = tmp_first_redir->next;
	}
	return (1);
}

static int	is_last_infile(t_redir_ms *first_redir)
{
	t_redir_ms *tmp_first_redir;

	tmp_first_redir = first_redir->next;
	while (tmp_first_redir)
	{
		if (tmp_first_redir->mode == TOK_INFILE)
			return (0);
		else if (tmp_first_redir->mode == TOK_HEREDOC)
			return (0);
		tmp_first_redir = tmp_first_redir->next;
	}
	return (1);
}

static t_node_ms	*get_mode_and_file(t_node_ms *binary_tree, t_redir_ms *first_redir)
{
	int	len_filename;

	len_filename = ft_strlen(first_redir->file_name);
	if (first_redir->mode == TOK_INFILE || first_redir->mode == TOK_HEREDOC)
	{
		binary_tree->infile = malloc((len_filename + 1) * sizeof(char));
		if (!binary_tree->infile)
			return (NULL);
		ft_strcpy(binary_tree->infile, first_redir->file_name);
		binary_tree->infile_mode = first_redir->mode;
	}
	else if (first_redir->mode == TOK_TRUNC || first_redir->mode == TOK_APPEND)
	{
		binary_tree->outfile = malloc((len_filename + 1) * sizeof(char));
		if (!binary_tree->outfile)
			return (NULL);
		ft_strcpy(binary_tree->outfile, first_redir->file_name);
		binary_tree->outfile_mode = first_redir->mode;
	}
	return (binary_tree);
}

t_node_ms	*get_redirections_modes_and_files(t_node_ms *binary_tree)
{
	t_redir_ms *first_redir;

	first_redir = binary_tree->first_redir;
	while (first_redir)
	{
		if (first_redir->mode == TOK_TRUNC || first_redir->mode == TOK_APPEND)
		{
			if (is_last_outfile(first_redir))
				binary_tree = get_mode_and_file(binary_tree, first_redir);
		}
		else if (first_redir->mode == TOK_INFILE
			|| first_redir->mode == TOK_HEREDOC)
		{
			if (is_last_infile(first_redir))
				binary_tree = get_mode_and_file(binary_tree, first_redir);
		}
		if (!binary_tree)
			return (NULL);
		first_redir = first_redir->next;
	}
	return (binary_tree);
}
