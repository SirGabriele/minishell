/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands_requested_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:08:52 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/27 20:18:54 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	child_n(t_pipex *pipex, int i, char **env)
{
	t_pipex_cmd	*copy;
	int			j;

	close(pipex->pipefd[i][0]);
	dup2(pipex->pipefd[i - 1][0], STD_IN);
	close(pipex->pipefd[i - 1][0]);
	dup2(pipex->pipefd[i][1], STD_OUT);
	close(pipex->pipefd[i][1]);
	j = -1;
	copy = pipex->first_cmd;
	while (++j < i)
		copy = copy->next;
	if (copy->correct_path == NULL)
		clear_program(pipex, NULL);
	if (execve(copy->correct_path, copy->tab_cmd, env) == -1)
		clear_program(pipex, "In child_n, execve failed");
}

static void	child_last(t_pipex *pipex, int i, char **argv, char **env)
{
	t_pipex_cmd	*copy;
	int			j;

	dup2(pipex->pipefd[i - 1][0], STD_IN);
	close(pipex->pipefd[i - 1][0]);
	pipex->outfile = open(argv[pipex->argc - 1], O_WRONLY | O_TRUNC);
	dup2(pipex->outfile, STD_OUT);
	close(pipex->outfile);
	copy = pipex->first_cmd;
	j = -1;
	while (++j < i)
		copy = copy->next;
	if (copy->correct_path == NULL)
		clear_program(pipex, NULL);
	if (execve(copy->correct_path, copy->tab_cmd, env) == -1)
		clear_program(pipex, "In child_last, execve failed");
}

static void	child_one(t_pipex *pipex, char **argv, char **env)
{
	t_pipex_cmd	*copy;

	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		dup2(pipex->pipefd[0][0], STD_IN);
		close(pipex->pipefd[0][0]);
		close(STD_IN);
		dup2(pipex->pipefd[0][1], STD_OUT);
		close(pipex->pipefd[0][1]);
		close(STD_OUT);
		close(STD_ERR);
		clear_program(pipex, NULL);
	}
	close(pipex->pipefd[0][0]);
	dup2(pipex->infile, STD_IN);
	close(pipex->infile);
	dup2(pipex->pipefd[0][1], STD_OUT);
	close(pipex->pipefd[0][1]);
	copy = pipex->first_cmd;
	if (copy->correct_path == NULL)
		clear_program(pipex, NULL);
	if (execve(copy->correct_path, copy->tab_cmd, env) == -1)
		clear_program(pipex, "In child_one, execve failed");
}

void	several_commands_requested(t_pipex *p, int ac, char **av, char **env)
{
	int	i;

	i = -1;
	while (++i < ac - 3)
	{		
		if (i < ac - 4 && pipe(p->pipefd[i]) == -1)
			clear_program(p, "In SCR.c, pipe failed");
		p->tab_pid[i] = fork();
		if (p->tab_pid[i] == -1)
			clear_program(p, "In SCR.c, fork failed");
		if (i == 0 && p->tab_pid[i] == 0)
			child_one(p, av, env);
		else if (i == ac - 4 && p->tab_pid[i] == 0)
			child_last(p, i, av, env);
		else if (p->tab_pid[i] == 0)
			child_n(p, i, env);
		if (i > 0 && i != ac - 4)
			close(p->pipefd[i - 1][0]);
		if (i < ac - 4)
			close(p->pipefd[i][1]);
	}
	close(p->pipefd[i - 2][0]);
	i = -1;
	while (++i < ac - 3)
		waitpid(p->tab_pid[i], NULL, WUNTRACED);
}
