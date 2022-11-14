/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_commands_requested_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:19:41 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/28 15:01:58 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	child_last(t_pipex *pipex, int *pipefd, char **argv, char **env)
{
	t_pipex_cmd	*copy;

	close(pipefd[1]);
	dup2(pipefd[0], STD_IN);
	close(pipefd[0]);
	pipex->outfile = open(argv[5], O_WRONLY | O_APPEND);
	dup2(pipex->outfile, STD_OUT);
	close(pipex->outfile);
	copy = pipex->first_cmd->next;
	if (copy->correct_path == NULL)
		clear_program(pipex, NULL);
	if (execve(copy->correct_path, copy->tab_cmd, env) == -1)
		clear_program(pipex, "Execve child_last failed");
}

static void	child_one(t_pipex *p, int *pipefd, char **env, int *pipehd)
{
	close(pipefd[0]);
	dup2(pipehd[0], STD_IN);
	dup2(pipefd[1], STD_OUT);
	close(pipefd[1]);
	if (p->first_cmd->correct_path == NULL)
		clear_program(p, NULL);
	if (execve(p->first_cmd->correct_path, p->first_cmd->tab_cmd, env) == -1)
		clear_program(p, "Execve child_one failed");
}

void	two_commands_requested(t_pipex *p, char **argv, char **env, int *pipehd)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		clear_program(p, "Pipe failed");
	pid1 = fork();
	if (pid1 == -1)
		clear_program(p, "Fork 1 failed");
	else if (pid1 == 0)
		child_one(p, pipefd, env, pipehd);
	pid2 = fork();
	if (pid2 == -1)
		clear_program(p, "Fork 2 failed");
	else if (pid2 == 0)
		child_last(p, pipefd, argv, env);
	close(pipefd[0]);
	close(pipefd[1]);
	close(pipehd[0]);
	waitpid(pid1, NULL, WUNTRACED);
	waitpid(pid2, NULL, WUNTRACED);
}
