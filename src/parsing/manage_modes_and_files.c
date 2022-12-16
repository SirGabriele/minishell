#include "../../includes/minishell.h"

static int	check_redir(t_redir_ms *first_redir)
{
	if (first_redir->mode == TOK_TRUNC)
		return (1);
	else if (first_redir->mode == TOK_APPEND)
		return (1);
	else if (first_redir->mode == TOK_INFILE)
		return (2);
	else if (first_redir->mode == TOK_HEREDOC)
		return (2);
	return (0);
}

static int	is_last_outfile(t_redir_ms *first_redir)
{
	t_redir_ms	*tmp_first_redir;

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
	t_redir_ms	*tmp_first_redir;

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

/************************************************************/
/*															*/
/*	Checks the outfile/infile mode of the command and gets	*/
/*	the names of the outfile/infile by calling				*/
/*	get_mode_and_file										*/
/*															*/
/*	Parameters:												*/
/*		binary_tree	-	node								*/
/*															*/
/*	Return:													*/
/*		binary_tree	-	edited node							*/
/*															*/
/************************************************************/

t_node_ms	*manage_modes_and_files(t_node_ms *binary_tree)
{
	t_redir_ms	*first_redir;

	first_redir = binary_tree->first_redir;
	while (first_redir)
	{
		if (is_last_outfile(first_redir) && check_redir(first_redir) == 1)
				binary_tree = get_mode_and_file(binary_tree, first_redir);
		else if (is_last_infile(first_redir) && check_redir(first_redir) == 2)
				binary_tree = get_mode_and_file(binary_tree, first_redir);
		if (!binary_tree)
			return (NULL);
		first_redir = first_redir->next;
	}
	return (binary_tree);
}
