#include "../../includes/minishell.h"

static int	check_infile(t_redir_ms *cursor)
{
	int	fd;

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

static int	check_outfile(t_redir_ms *cursor)
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

static int	manage_infiles_outfiles(t_redir_ms *first_redir)
{
	t_redir_ms	*cursor;

	cursor = first_redir;
	while (cursor != NULL)
	{
		if (cursor->mode == TOK_INFILE)
		{
			if (check_infile(cursor) == -1)
				return (-1);
		}
		else
		{
			if (check_outfile(cursor) == -1)
				return (-1);
		}
		cursor = cursor->next;
	}
	return (0);
}

int	launch_pipex(t_pipeline_ms *pipeline)
{
	if (manage_infiles_outfiles(pipeline->first_redir) == -1)
		return (-1);
	//check infiles/outfiles
	exec_pipex(pipeline);
	return (0);
}
