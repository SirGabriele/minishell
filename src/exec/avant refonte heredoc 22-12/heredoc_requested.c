#include "../../includes/minishell.h"

static void	sent_eof_in_heredoc(int line, const char *delimiter)
{
	ft_printf_fd(2, "minishell: warning: here-document at line %d delimited "\
		"by end-of-file (wanted `%s')\n", line, delimiter);
}

/****************************************************************/
/*																*/
/*	Triggers an interactive mode and does not write into	 	*/
/*		anything until the correct delimiter is written			*/
/*																*/
/*	Parameters:													*/
/*		delimiter	-	the correct delimiter					*/
/*																*/
/*	Return:														*/
/*		 0	-	the delimiter has been written					*/
/*		-1	-	the user send EOF								*/
/*																*/
/****************************************************************/

static int	fake_heredoc_requested(const char *delimiter)//faire un signal adapté pour heredoc
{
	char	*user_input;
	int		length_delimiter;
	int		line;

	line = 0;
	length_delimiter = ft_strlen(delimiter);
	while (1)
	{
		user_input = readline("> ");
		if (!user_input)
		{
			sent_eof_in_heredoc(line, delimiter);
			return (-1);
		}
		if (ft_strncmp(user_input, delimiter, length_delimiter) == 0
			&& user_input[length_delimiter + 1] == '\0')
		{
			free(user_input);
			break ; //si besoin de ligne, mettre lefree en dehors du while
		}
		free(user_input);
		line++;
		user_input = NULL;
	}
	return (0);
}

/****************************************************************/
/*																*/
/*	Triggers an interactive mode and writes the specified lines	*/
/*		into pipe_before until the correct delimiter is written	*/
/*																*/
/*	Parameters:													*/
/*		delimiter	-	the correct delimiter					*/
/*		pipe_before	-	the pipe that will be used as input		*/
/*																*/
/*	Return:														*/
/*		 0	-	the pipe was correctly filled					*/
/*																*/
/****************************************************************/

static int	real_heredoc_requested(const char *delimiter, int *pipe_before)//faire un signal adapté pour heredoc
{
	char	*user_input;
	int		length_delimiter;
	int		line;

	line = 0;
	length_delimiter = ft_strlen(delimiter);
	while (1)
	{
		user_input = readline("> ");
		if (!user_input)
		{
			sent_eof_in_heredoc(line, delimiter);
			return (-1);
		}
		if (ft_strncmp(user_input, delimiter, length_delimiter) == 0
			&& user_input[length_delimiter + 1] == '\0')
			break ;
		ft_putstr_fd(user_input, pipe_before[1]);
		ft_putstr_fd("\n", pipe_before[1]);
		free(user_input);
		line++;
		user_input = NULL;
	}
	free(user_input);
	return (0);
}

/****************************************************************/
/*																*/
/*	Counts the amount of heredoc redirections associated to		*/
/*		this command in case of several heredocs with the same	*/
/*		delimiter												*/
/*																*/
/*	Parameters:													*/
/*		first_redir	-	a linked list containing all the		*/
/*						redirections associated to this	command	*/
/*		infile		-	the name of the infile to be used		*/
/*																*/
/*	Return:														*/
/*		count	-	the amount of found heredocs				*/
/*																*/
/****************************************************************/

static int	get_position_good_heredoc(t_redir_ms *first_redir,
	const char *infile)
{
	t_redir_ms	*cursor;
	int			len_delimiter;
	int			count;

	cursor = first_redir;
	len_delimiter = ft_strlen(infile);
	count = 0;
	while (cursor != NULL)
	{
		if (ft_strncmp(cursor->file_name, infile, len_delimiter) == 0
			&& cursor->file_name[len_delimiter] == '\0')
			count++;
		cursor = cursor->next;
	}
	return (count);
}

int	heredoc_requested(t_redir_ms *redir, t_node_ms *node, int *pipe_before, int *marker)//gestion signaux a ajouter
{
	int			len_delim;

	len_delim = ft_strlen(node->infile);
	if (*marker == 0)
		(*marker) = get_position_good_heredoc(node->first_redir, node->infile);
	if (ft_strncmp(redir->file_name, node->infile, len_delim) == 0
		&& (*marker) == 1)
	{
		if (real_heredoc_requested(redir->file_name, pipe_before) == -1)
			return (-1);
	}
	else
	{
		if (fake_heredoc_requested(redir->file_name) == -1)
			return (-1);
		(*marker)--;
	}
	return (0);
}
