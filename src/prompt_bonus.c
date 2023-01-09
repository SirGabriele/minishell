#include "../includes/minishell.h"

static int	is_exit(char *user_input)
{
	if (!user_input)
	{
		rl_clear_history();
		write(1, "exit\n", 5);
		return (0);
	}
	if (ft_strncmp(user_input, "exit", 4) == 0)
	{
		rl_clear_history();
		free(user_input);
		return (0);
	}
	return (1);
}

int	cmd_prompt(t_env_ms *env_ll)
{
	char	*user_input;
	char	*pwd_prompt;
	int		ret;

	while (1)
	{
		pwd_prompt = get_pwd_prompt(env_ll);
		user_input = readline(pwd_prompt);
		free(pwd_prompt);
		if (is_exit(user_input) == 0)
			return (0);
		ret = ft_check_all_syntax_error(&user_input, env_ll);
		if (ret == 3)
			return (3);
		if (user_input && ft_strlen(user_input) > 0)
			add_history(user_input);
		if (ret != 0)
		{
			free(user_input);
			continue ;
		}
		if (user_input && launch_program(&user_input, env_ll) == -1)
			return (-1);
	}
	return (3);
}
