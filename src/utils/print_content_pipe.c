#include "../../includes/minishell.h"

void	print_content_pipe(int *pipe, t_env_ms *env_ll)
{
	char	**env_arr;
	char	**content;
	char	*cat_path;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		dup2(pipe[0], 0);
		close(pipe[0]);
		close(pipe[1]);
		content = malloc(sizeof(char *) * 2);
		content[0] = ft_strdup("cat");
		content[1] = NULL;
		env_arr = convert_env_ll_into_arr(env_ll);
		cat_path = verify_cmd_path("cat", env_arr);
		execve(cat_path, content, env_arr);
		free_double_arr(env_arr);
		free_double_arr(content);
		free(cat_path);
	}
}
