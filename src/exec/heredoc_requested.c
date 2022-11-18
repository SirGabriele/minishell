#include "../../includes/minishell.h"

static int	read_loop(int std_in_copy, const char *delimiter, int *pipehd)
{
	char	*user_input;
	int		length_delimiter;

	length_delimiter = ft_strlen(delimiter);
	while (1)
	{
		write(1, ">", 1);
		user_input = get_next_line(std_in_copy);
		if (ft_strncmp(user_input, delimiter, length_delimiter) == 0
			&& user_input[length_delimiter + 1] == '\0')
		{
			if (close(std_in_copy) == -1)
				return (-1);
			free(user_input);
			user_input = get_next_line(std_in_copy);
			if (close(pipehd[1]) == -1)
				return (-1);
			break ;
		}
		ft_pustr_fd(user_input, pipehd[1]);
		free(user_input);
		user_input = NULL;
	}
	return (0);
}

int	fake_heredoc_requested(const char *delimiter, int std_in_copy)
{
	char	*user_input;
	int		length_delimiter;

	length_delimiter = ft_strlen(delimiter);
	while (1)
	{
		write(1, ">", 1);
		user_input = get_next_line();
		if (ft_strncmp(user_input, delimiter, length_delimiter) == 0
			&& user_input[length_delimiter + 1] == '\0')
		{
			if (close(std_in_copy) == -1)
				return (-1);
			free(user_input);
			user_input = get_next_line(std_in_copy);
			break ;
		}
		free(user_input);
		user_input = NULL;
	}
	return (0);
}

/************************************************************/
/*															*/
/*	Triggers the filling process of the infile pipe if an 	*/
/*	heredoc	has been requested								*/
/*															*/
/*	Parameters:												*/
/*		context - the first pipeline						*/
/*															*/
/*	Return:													*/
/*		-1 - if an error occured							*/
/*		 0 - if everything is fine							*/
/*															*/
/************************************************************/
int	real_heredoc_requested(t_context_ms *context, int std_in_copy)
{
	int	pipehd[2];

	if (pipe(pipehd) == -1)
		return (-1);
	if (read_loop(std_in_copy, context->all_redirs->infile, pipehd,) == -1)
		return (-1);
	if (close(pipehd[0]) == -1)
		return (-1);
	return (0);
}
