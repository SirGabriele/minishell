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
		ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			cursor->file_name);
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

/************************************************************/
/*															*/
/*	Verifies if all the infiles and outfile written in the	*/
/*	command line are all valid								*/
/*															*/
/*	Parameters:												*/
/*		context - all the pipelines							*/
/*															*/
/*	Return:													*/
/*		-1 - if an error occured							*/
/*		 0 - if everything is fine							*/
/*															*/
/************************************************************/
static int	verify_all_redirs(t_context_ms *context)
{
	t_context_ms	*cursor_cont;
	t_redir_ms		*cursor_redir;

	cursor_cont = context;
	while (cursor_cont != NULL)
	{
		cursor_redir = cursor_cont->all_redirs->first_redir;
		while (cursor_redir != NULL)
		{
			if (cursor_redir->mode == TOK_INFILE
				|| cursor_redir->mode == TOK_HEREDOC)
			{
				if (verify_infiles(cursor_redir) == -1)
					return (-1);
			}
			else
			{
				if (verify_outfiles(cursor_redir) == -1)
					return (-1);
			}
			cursor_redir = cursor_redir->next;
		}
		cursor_cont = cursor_cont->next;
	}
	return (0);
}

int	launch_pipex(t_context_ms *context)
{
	if (verify_all_redirs(context) == -1)
		return (-1);
	return (0);
}
