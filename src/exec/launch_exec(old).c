#include "../../includes/minishell.h"

static int	verify_all_outfiles(t_redir_ms *cursor)
{
	int	fd;

	if (cursor->mode == TOK_TRUNC)
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
/*	Splits the verification depending on if the redirection	*/
/*	is in or out											*/
/*															*/
/*	Parameters:												*/
/*		context - the first pipeline						*/
/*		first_redir - the first redirection					*/
/*		infile - the file that will be used as main infile	*/
/*															*/
/*	Return:													*/
/*		-1 - if an error occured							*/
/*		 0 - if everything is fine							*/
/*															*/
/************************************************************/
static int	verify_each_redir(t_context_ms *context, t_redir_ms *first_redir,
	const char *infile)
{
	t_redir_ms		*cursor;

	cursor = first_redir;
	while (cursor != NULL)
	{
		if (cursor->mode == TOK_INFILE)
		{
			if (verify_basic_infile(cursor) == -1)
				return (-1);
		}
		else if (cursor->mode == TOK_HEREDOC)
		{
			if (handle_append_infile(context, cursor, infile) == -1)
				return (-1);
		}
		else
		{
			if (verify_all_outfiles(cursor) == -1)
				return (-1);
		}
		cursor = cursor->next;
	}
	return (0);
}

/************************************************************/
/*															*/
/*	Verifies if all the infiles and outfiles written in the	*/
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
	t_context_ms	*cursor;

	cursor = context;
	while (cursor != NULL)
	{
		if (verify_each_redir(context, cursor->all_redirs->first_redir,
				context->all_redirs->infile) == -1)
			return (-1);
		cursor = cursor->next;
	}
	return (0);
}

int	launch_exec(t_context_ms *context)
{
	t_context_ms	*current_cont;

	if (verify_all_redirs(context) == -1)
		return (-1);
//	if (exec_pipex(context) == -1)
//		return (-1);
	current_cont = context;
/*	while (current_cont != NULL)
	{
		if (how_to_handle_this_pipeline(current_cont, context) == -1)
			return (-1);
		current_cont = current_cont->next;
	}*/
	return (0);
}
