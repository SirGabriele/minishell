/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:54:51 by kbrousse          #+#    #+#             */
/*   Updated: 2022/12/08 18:22:03 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	int	pipefd[2];
	char	**tab;
	char	**arr;
	char	*buf;
	int		fd;
	int		i = 0;
	pid_t	child;

	fd = open("infile.txt", O_RDONLY);
	tab = malloc(sizeof(char *) * 2);
	arr = malloc(sizeof(char *) * 3);
	buf = malloc(sizeof(char) * 500);
	tab[0] = "/bin/cat";
	tab[1] = NULL;
	arr[0] = "/usr/bin/echo";
	arr[1] = "test";
	arr[2] = NULL;
	pipe(pipefd);
	child = fork();
	if (child == 0)
	{
		close(pipefd[0]);
		dup2(fd, 0);
		close(fd);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execve(arr[0], arr, env);
		exit(1);
	}
	waitpid(child, NULL, WUNTRACED);
	child = fork();
	if (child == 0)
	{
		close(pipefd[1]);
		i = read(pipefd[0], buf, 400);
		write(1, buf, i);
		close(pipefd[0]);
	}
/*	if (child == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		execve(tab[0], tab, env);
		exit(1);
	}*/
	waitpid(child, NULL, WUNTRACED);
	close(pipefd[1]);
	close(pipefd[0]);
	free(arr);
	free(tab);
	free(buf);
	return (1);
}
