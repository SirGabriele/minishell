#include "../../includes/minishell.h"

static int	verify_infiles(t_redir_ms *cursor)
{
	int	fd;

	if (cursor->mode == TOK_HEREDOC)
//		if (launch_heredoc() == -1) // TO CODE
			return (-1);
	fd = open(cursor->file_name, O_WRONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n", cursor->file_name);
		return (-1);
	}
	if (close(fd) == -1)
	{
		ft_printf_fd(2, "Error upon closing %s\n", cursor->file_name);
		return (-1);
	}
	return (0);
}

static int	verify_outfiles(t_redir_ms *cursor)
{
	int	fd;

	if (cursor->mode == TOK_OUTF_TRUNC)
		fd = open(cursor->file_name, O_CREAT | O_TRUNC, 0644);
	else
		fd = open(cursor->file_name, O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf_fd(2, "Error upon opening %s\n", cursor->file_name);
		return (-1);
	}
	if (close(fd) == -1)
	{
		ft_printf_fd(2, "Error upon closing %s\n", cursor->file_name);
		return (-1);
	}
	return (0);
}

static int	verify_all_redirs(t_redir_ms *first_redir)
{
	t_redir_ms	*cursor;

	cursor = first_redir;
	while (cursor != NULL)
	{
		if (cursor->mode == TOK_INFILE || cursor->mode == TOK_HEREDOC)
		{
			if (verify_infiles(cursor) == -1)
				return (-1);
		}
		else
		{
			if (verify_outfiles(cursor) == -1)
				return (-1);
		}
		cursor = cursor->next;
	}
	return (0);
}

int	launch_pipex(t_context_ms *context)
{
	t_context_ms	*cursor;

	cursor = context;
	while (cursor != NULL)
	{
		if (verify_all_redirs(cursor->all_redirs->first_redir) == -1)
			return (-1);
		cursor = cursor->next;
	}
	return (0);
}
