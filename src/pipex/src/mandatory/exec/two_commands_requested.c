/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_commands_requested.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:19:41 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/27 20:20:03 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	child_last(t_pipex *pipex, int *pipefd, char **argv, char **env)
{
	t_pipex_cmd	*copy;

	close(pipefd[1]);
	dup2(pipefd[0], STD_IN);
	close(pipefd[0]);
	pipex->outfile = open(argv[4], O_WRONLY | O_TRUNC);
	dup2(pipex->outfile, STD_OUT);
	close(pipex->outfile);
	copy = pipex->first_cmd->next;
	if (copy->correct_path == NULL)
		clear_program(pipex, NULL);
	if (execve(copy->correct_path, copy->tab_cmd, env) == -1)
		clear_program(pipex, "Execve child_last failed");
}

static void	child_one(t_pipex *p, int *pipefd, char **argv, char **env)
{
	p->infile = open(argv[1], O_RDONLY);
	if (p->infile == -1)
	{
		dup2(pipefd[0], STD_IN);
		close(pipefd[0]);
		close(STD_IN);
		dup2(pipefd[1], STD_OUT);
		close(pipefd[1]);
		close(STD_OUT);
		close(STD_ERR);
		clear_program(p, NULL);
	}
	close(pipefd[0]);
	dup2(p->infile, STD_IN);
	close(p->infile);
	dup2(pipefd[1], STD_OUT);
	close(pipefd[1]);
	if (p->first_cmd->correct_path == NULL)
		clear_program(p, NULL);
	if (execve(p->first_cmd->correct_path, p->first_cmd->tab_cmd, env) == -1)
		clear_program(p, "Execve child_one failed");
}

void	two_commands_requested(t_pipex *pipex, char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		clear_program(pipex, "Pipe failed");
	pid1 = fork();
	if (pid1 == -1)
		clear_program(pipex, "Fork 1 failed");
	else if (pid1 == 0)
		child_one(pipex, pipefd, argv, env);
	pid2 = fork();
	if (pid2 == -1)
		clear_program(pipex, "Fork 2 failed");
	else if (pid2 == 0)
		child_last(pipex, pipefd, argv, env);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, WUNTRACED);
	waitpid(pid2, NULL, WUNTRACED);
}
