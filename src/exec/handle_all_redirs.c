#include "../../includes/minishell.h"

static int	outfile_mode(t_redir_ms *redir)
{
	int	fd;

	fd = open(redir->file_name, O_CREAT, 0644);
	if (access(redir->file_name, W_OK) == -1)
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", redir->file_name);
		return (1);
	}
	if (fd == -1)
	{
		ft_printf_fd(2, "Error upon opening %s\n", redir->file_name);
		return (1);
	}
	if (close(fd) == -1)
	{
		ft_printf_fd(2, "Error upon closing %s\n", redir->file_name);
		return (1);
	}
	return (0);
}

static int	verify_simple_infile(t_redir_ms *redir)
{
	int	fd;

	fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
	{
		if (access(redir->file_name, F_OK) == -1)
		{
			ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			redir->file_name);
		}
		else
		{
			ft_printf_fd(2, "minishell: %s: Permission denied\n",
			redir->file_name);
		}
		return (1);
	}
	if (close(fd) == -1)
	{
		ft_printf_fd(2, "Error upon closing %s\n", redir->file_name);
		return (1);
	}
	return (0);
}

static int	infile_mode(t_redir_ms *redir, int *pipe_before)
{
	int	exit_code;

	if (redir->mode == TOK_INFILE)
	{
		exit_code = verify_simple_infile(redir);
		if (exit_code != 0)
			return (exit_code);
	}
	else
	{
		exit_code = heredoc_requested(redir, pipe_before);
		if (exit_code != 0)
			return (exit_code);
	}
	return (0);
}

/********************************************************************/
/*																	*/
/*	Verifies the existence of all infiles and creates all outfiles	*/
/*																	*/
/*	Parameters:														*/
/*		pipes		-	structure containing the two pipes			*/
/*		children	-	structure containing the fork-linked		*/
/*						variables									*/
/*		node		-	node of the binary tree	to process			*/
/*		marker		-	int that will be used in the heredoc		*/
/*						part										*/
/*																	*/
/*	Return:															*/
/*		 exit_code	-	the exit_code								*/
/*																	*/
/********************************************************************/

int	handle_all_redirs(t_node_ms *node, int *pipe_before)
{
	t_redir_ms	*redir;
	int			exit_code;

	if (node->first_redir == NULL)
		return (0);
	redir = node->first_redir;
	while (redir != NULL)
	{
		if (redir->mode == TOK_INFILE || redir->mode == TOK_HEREDOC)
		{
			exit_code = infile_mode(redir, pipe_before);
			if (exit_code != 0)
				return (exit_code);
		}
		else if (redir->mode == TOK_TRUNC || redir->mode == TOK_APPEND)
		{
			exit_code = outfile_mode(redir);
			if (exit_code != 0)
				return (exit_code);
		}
		redir = redir->next;
	}
	return (0);
}
