#include "../../includes/minishell.h"

//faire un signal adapté pour heredoc, juste au dessus de readline
static int	fake_heredoc_requested(const char *delimiter)
{
	char	*user_input;
	int		length_delimiter;

	length_delimiter = ft_strlen(delimiter);
	while (1)
	{
		user_input = readline("heredoc> ");
		if (ft_strncmp(user_input, delimiter, length_delimiter) == 0
			&& user_input[length_delimiter + 1] == '\0')
		{
			free(user_input);
			break ;
		}
		free(user_input);
		user_input = NULL;
	}
	return (0);
}

static int	real_heredoc_requested(const char *delimiter, int *pipe_before)
{
	char	*user_input;
	int		length_delimiter;

	length_delimiter = ft_strlen(delimiter);
	while (1)
	{
		user_input = readline("heredoc> ");
		if (ft_strncmp(user_input, delimiter, length_delimiter) == 0
			&& user_input[length_delimiter + 1] == '\0')
		{
			free(user_input);
			break ;
		}
		ft_putstr_fd(user_input, pipe_before[1]);
		ft_putstr_fd("\n", pipe_before[1]);
		free(user_input);
		user_input = NULL;
	}
	return (0);
}

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

int	heredoc_requested(t_redir_ms *redir, t_node_ms *node, int *pipe_before, int *marker)
{
	int			len_delim;

	len_delim = ft_strlen(node->infile);
	if (*marker == 0)
		(*marker) = get_position_good_heredoc(node->first_redir, node->infile);
	if (ft_strncmp(redir->file_name, node->infile, len_delim) == 0
		&& (*marker) == 1)
	{
/*		close(pipe_before[0]);
		close(pipe_before[1]);
		pipe(pipe_before);*/
		printf("Good heredoc triggered\n");//A VIRER
		if (real_heredoc_requested(redir->file_name, pipe_before) == -1)
			return (-1);
	}
	else
	{
		printf("Useless heredoc triggered\n");//A VIRER
		if (fake_heredoc_requested(redir->file_name) == -1)
			return (-1);
		(*marker)--;
	}
	return (0);
}
