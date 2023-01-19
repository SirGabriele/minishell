/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:47:12 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 23:45:31 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>

int	is_permission_denied(char *content)
{
	if (ft_strncmp (content, "./", 2) == 0)
	{
		if (access(content, F_OK) == 0
			&& (access(content, R_OK) != 0
				|| access(content, X_OK) != 0))
		{
			ft_printf_fd(2, "minishell: %s: Permission denied\n", content);
			return (0);
		}
	}
	return (1);
}

int	is_a_directory(char *content)
{
	DIR	*dir;
	int	len;

	len = ft_strlen(content);
	if (content[0] == '/' || ft_strncmp (content, "./", 2) == 0
		|| content[len - 1] == '/')
	{
		dir = opendir(content);
		if (dir != NULL)
		{
			ft_printf_fd(2, "minishell: %s: Is a directory\n", content);
			closedir(dir);
			return (0);
		}
	}
	return (1);
}

static char	*get_cmd_path(char *user_input_cmd, char **env_paths_arr)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (user_input_cmd[0] == '\0' || ft_strcmp(user_input_cmd, ".") == 0)
	{
		ft_printf_fd(2, "%s: command not found\n", user_input_cmd);
		return (NULL);
	}
	while (env_paths_arr[i] != NULL)
	{
		cmd_path = ft_strjoin(env_paths_arr[i], "/");
		cmd_path = ft_strjoin_free_first(cmd_path, user_input_cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	ft_printf_fd(2, "%s: command not found\n", user_input_cmd);
	return (NULL);
}

static char	*get_env_path_var(char **env_arr)
{
	char	*path;
	int		i;

	i = 0;
	while (env_arr[i] != NULL && ft_strncmp(env_arr[i], "PATH=", 5) != 0)
		i++;
	if (env_arr[i] == NULL)
		return (NULL);
	path = ft_strdup(env_arr[i]);
	return (path);
}

/****************************************************************/
/*																*/
/*	Verifies if the requested command already includes its		*/
/*		correct path. If it does not, seeks its correct			*/
/*		path													*/
/*																*/
/*	Parameters:													*/
/*		user_input_cmd	-	the command written by the user		*/
/*		env_arr			-	double array containing the end		*/
/*							variables							*/
/*																*/
/*	Return:														*/
/*		cmd_path	-	the correct command's path				*/
/*		NULL		-	the command's path was not found		*/
/*																*/
/****************************************************************/

char	*verify_cmd_path(char *user_input_cmd, char **env_arr)
{
	char	**env_paths_arr;
	char	*env_path_var;
	char	*cmd_path;

	if (access(user_input_cmd, F_OK) == 0
		&& access(user_input_cmd, X_OK) == 0)
		return (user_input_cmd);
	env_path_var = get_env_path_var(env_arr);
	if (env_path_var == NULL || ((user_input_cmd[0] == '/'
				|| ft_strncmp (user_input_cmd, "./", 2) == 0)
			&& access(user_input_cmd, F_OK) != 0))
	{
		free(env_path_var);
		ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			user_input_cmd);
		return (NULL);
	}
	env_paths_arr = ft_split(env_path_var + 5, ':');
	if (env_paths_arr == NULL)
		return (NULL);
	cmd_path = get_cmd_path(user_input_cmd, env_paths_arr);
	free_double_arr(env_paths_arr);
	free(env_path_var);
	return (cmd_path);
}
