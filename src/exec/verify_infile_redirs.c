#include "../../includes/minishell.h"

int	verify_basic_infile(t_redir_ms *cursor)
{
	int	fd;

	fd = open(cursor->file_name, O_RDONLY);
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

/************************************************************/
/*															*/
/*	Sorts the different heredocs requested. If that's a		*/
/*	useless one, it will not write anywhere. If that's a	*/
/*	useful one it will write in the infile_pipe				*/
/*															*/
/*	Parameters:												*/
/*		context - the first pipeline						*/
/*		cursor - a cursor on the current redirection struct	*/
/*		infile - the delimiter associated to the useful		*/
/*			heredoc											*/
/*															*/
/*	Return:													*/
/*		-1 - if an error occured							*/
/*		 0 - if everything is fine							*/
/*															*/
/************************************************************/
int	handle_append_infile(t_context_ms *context, t_redir_ms *cursor,
	const char *infile)
{
	int	len_infile;
	int	std_in_copy;

	pid_t	child;
	
	child = fork();
	if (child == 0)
	{
		std_in_copy = dup(0);
		len_infile = ft_strlen(context->all_redirs->infile);
		if (ft_strncmp(cursor->file_name, infile, len_infile) == 0)
		{
			if (real_heredoc_requested(context, std_in_copy) == -1)
				return (-1);
		}
		else
		{
			if (fake_heredoc_requested(cursor->file_name, std_in_copy) == -1)
				return (-1);
		}
		exit(0);
	}
	return (0);
}
