#include "../../includes/minishell.h"

static char	*get_cmd_path(char *user_input_cmd, char **env_paths_arr)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (env_paths_arr[i] != NULL)
	{
		cmd_path = ft_strjoin(env_paths_arr[i], "/");
		cmd_path = ft_strjoin_free_first(cmd_path, user_input_cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (NULL);
}

static char	*get_env_path_var(char **env_arr)
{
	char	*path;
	int	i;

	i = 0;
	while (ft_strncmp(env_arr[i], "PATH=", 5) != 0 && env_arr[i] != NULL)
		i++;
	if (env_arr[i] == NULL)
	{
		ft_putstr_fd("PATH variable not found\n", 2);//A VIRER
		return (NULL);
	}
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

	if (access(user_input_cmd, F_OK) == 0)
		return (user_input_cmd);
	env_path_var = get_env_path_var(env_arr);
	if (env_path_var == NULL)
		return (NULL);
	env_paths_arr = ft_split(env_path_var + 5, ':');
	if (env_paths_arr == NULL)
		return (NULL);
	cmd_path = get_cmd_path(user_input_cmd, env_paths_arr);
	free_double_arr(env_paths_arr);
	free(env_path_var);
	return (cmd_path);
}

