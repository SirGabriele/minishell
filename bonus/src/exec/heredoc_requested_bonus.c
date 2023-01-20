/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_requested_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:15:42 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:15:43 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void	free_memory_fork_and_exit(t_pipes_ms *pipes,
	t_env_ms *env_ll, int exit_code)
{
	free_binary_tree(pipes->tree_root);
	free_env_list(env_ll);
	free(pipes->children->pid_arr);
	free(pipes->children);
	close(pipes->before[0]);
	close(pipes->before[1]);
	close(pipes->after[1]);
	close(pipes->after[0]);
	free(pipes);
	close(0);
	close(1);
	close(2);
	exit(exit_code);
}

static void	sent_eof_in_heredoc(int line, const char *delimiter)
{
	if (g_signal != 130)
		ft_printf_fd(2, "minishell: warning: here-document at line" \
			" %d delimited by end-of-file (wanted `%s')\n", line, delimiter);
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

static void	trigger_heredoc(const char *delimiter, t_pipes_ms *pipes,
	t_env_ms *env_ll)
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
			free_memory_fork_and_exit(pipes, env_ll, g_signal);
		}
		else if (ft_strncmp(user_input, delimiter, length_delimiter) == 0
			&& user_input[length_delimiter] == '\0')
			break ;
		expand_dollar_heredoc(user_input, pipes, env_ll);
		free(user_input);
		line++;
	}
	free(user_input);
	free_memory_fork_and_exit(pipes, env_ll, 0);
}

int	heredoc_requested(t_redir_ms *redir, t_pipes_ms *pipes, t_env_ms *env_ll)
{
	pid_t	child;
	int		ret;
	int		wstatus;

	ret = 0;
	if (close(pipes->before[0]) == -1 || close(pipes->before[1]) == -1)
		return (-1);
	if (pipe(pipes->before) == -1)
		return (-1);
	child = fork();
	if (child == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler_heredoc);
		trigger_heredoc(redir->file_name, pipes, env_ll);
	}
	wstatus = 0;
	waitpid(child, &wstatus, WUNTRACED);
	if (WIFEXITED(wstatus))
		ret = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		ret = WTERMSIG(wstatus) + 128;
	return (ret);
}
