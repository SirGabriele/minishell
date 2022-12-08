#include "../../includes/minishell.h"

static int	outfile_mode(t_redir_ms *redir)
{
	int	fd;

	fd = open(redir->file_name, O_CREAT, 0644);
	if (fd == -1)
	{
		ft_printf_fd(2, "Error upon opening %s\n", redir->file_name);
		return (-1);
	}
	if (close(fd) == -1)
	{
		ft_printf_fd(2, "Error upon closing %s\n", redir->file_name);
		return (-1);
	}
	return (0);
}

static int	verify_simple_infile(t_redir_ms *redir)
{
	int	fd;

	fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "Minishell: %s: No such file or directory\n",
			redir->file_name);
		return (-1);
	}
	if (close(fd) == -1)
	{
		ft_printf_fd(2, "Error upon closing %s\n", redir->file_name);
		return (-1);
	}
	return (0);
}

static int	infile_mode(t_redir_ms *redir, t_node_ms *node, int *pipe_before)
{
	if (redir->mode == TOK_INFILE)
	{
		if (verify_simple_infile(redir) == -1)
			return (-1);
	}
	else
	{
		if (heredoc_requested(redir, node, pipe_before) == -1)
			return (-1);
	}
	return (0);
}

int	handle_all_redirs(t_node_ms *node, int *pipe_before)
{
	t_redir_ms	*redir;

	if (node->first_redir == NULL)
		return (0);
	redir = node->first_redir;
	while (redir != NULL)
	{
//		printf("%s | %d\n", redir->file_name, redir->mode);//A VIRER
		if (redir->mode == TOK_INFILE || redir->mode == TOK_HEREDOC)
		{
			if (infile_mode(redir, node, pipe_before) == -1)
				return (-1);
		}
		else if (redir->mode == TOK_TRUNC || redir->mode == TOK_APPEND)
		{
			if (outfile_mode(redir) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
