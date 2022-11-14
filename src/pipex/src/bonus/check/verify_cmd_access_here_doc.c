/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_cmd_access_here_doc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:46:01 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/27 15:47:53 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static void	verify_access(t_pipex *pipex, t_pipex_cmd *copy)
{
	int			i;
	char		*path_line;
	char		*path_line_temp;

	i = -1;
	while (++i < 10)
	{
		path_line_temp = ft_strjoin(pipex->tab_env_paths[i], "/");
		path_line = ft_strjoin(path_line_temp, copy->tab_cmd[0]);
		free(path_line_temp);
		path_line_temp = NULL;
		if (access(path_line, F_OK) == -1 && i == 9)
		{
			free(path_line);
			copy->correct_path = NULL;
			return ;
		}
		else if (access(path_line, F_OK) == 0)
			break ;
		free(path_line);
		path_line = NULL;
	}
	copy->correct_path = ft_strdup(path_line);
	free(path_line);
	path_line = NULL;
}

static void	fill_tab_cmd(t_pipex *pipex, int argc, char **argv)
{
	t_pipex_cmd	*copy;
	int			i;

	copy = pipex->first_cmd;
	i = 2;
	while (copy != NULL && ++i < argc - 1)
	{
		copy->tab_cmd = ft_split(argv[i], ' ');
		copy = copy->next;
	}
}

static void	extract_path_lines(t_pipex *pipex, char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			pipex->tab_env_paths = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (env[i] == NULL)
		clear_program(pipex, "Path line not found");
}

void	verify_cmd_access_here_doc(t_pipex *p, int ac, char **av, char **env)
{
	int			i;
	t_pipex_cmd	*copy;

	i = 2;
	copy = p->first_cmd;
	extract_path_lines(p, env);
	fill_tab_cmd(p, ac, av);
	copy = p->first_cmd;
	while (++i < ac - 1)
	{
		if (access(copy->tab_cmd[0], F_OK) == 0)
			copy->correct_path = ft_strdup(copy->tab_cmd[0]);
		else
			verify_access(p, copy);
		copy = copy->next;
	}
}
