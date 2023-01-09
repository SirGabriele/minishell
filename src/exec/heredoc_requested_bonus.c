#include "../../includes/minishell.h"

static void	sent_eof_in_heredoc(int line, const char *delimiter, t_pipes_ms *pipes)
{
	ft_printf_fd(2, "minishell: warning: here-document at line %d delimited "\
		"by end-of-file (wanted `%s')\n", line, delimiter);
	close(pipes->before[0]);
	close(pipes->before[1]);
	close(pipes->after[0]);
	close(pipes->after[1]);
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

static int	trigger_heredoc(const char *delimiter, t_pipes_ms *pipes, t_env_ms *env_ll)//faire un signal adapté pour heredoc
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
			sent_eof_in_heredoc(line, delimiter, pipes);
			return (-1);
		}
		if (ft_strncmp(user_input, delimiter, length_delimiter) == 0
			&& user_input[length_delimiter] == '\0')//enlevé le +1 de l'index
			break ;
		expand_dollar_heredoc(user_input, pipes, env_ll);
		free(user_input);
		line++;
		user_input = NULL;
	}
	free(user_input);
	return (0);
}

int	heredoc_requested(t_redir_ms *redir, t_pipes_ms *pipes, t_env_ms *env_ll)//gestion signaux a ajouter
{
	if (close(pipes->before[0]) == -1 || close(pipes->before[1]) == -1)
		return (-1);
	if (pipe(pipes->before) == -1)
		return (-1);
	if (trigger_heredoc(redir->file_name, pipes, env_ll) == -1)
		return (-1);
	return (0);
}
