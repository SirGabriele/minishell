#include "../../includes/minishell.h"

static void	free_arr_env_paths(char **arr_env_paths)
{
	int	i;

	i = 0;
	while (arr_env_paths[i] != NULL)
	{
		free(arr_env_paths[i]);
		i++;
	}
	free(arr_env_paths);
	arr_env_paths = NULL;
}

static char	*get_correct_path(char **arr_env_paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (arr_env_paths[i] != NULL)
	{
		path = ft_strjoin(arr_env_paths[i], "/");
		path = ft_strjoin_free_first(path, cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

t_cmd_list_ms	*ft_lstnew_cmd(char *cmd_and_args) //faire la copy de env et recoder mon propre getenv
{
	t_cmd_list_ms	*elem;
	char			**arr_env_paths;//A VIRER?

	elem = malloc(sizeof(t_cmd_list_ms));
	if (!elem)
		return (NULL);
	elem->cmd_and_args = ft_split(cmd_and_args, ' ');
	arr_env_paths = ft_split(getenv("PATH"), ':');//A VIRER?
	elem->correct_path = get_correct_path(arr_env_paths, elem->cmd_and_args[0]);
	free_arr_env_paths(arr_env_paths);
	if (elem->correct_path == NULL)
		return (NULL);
	elem->next = NULL;
	return (elem);
}
