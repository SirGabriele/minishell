#include "../includes/minishell_bonus.h"

static int	is_exit(char *user_input)
{
	int	i;

	if (!user_input)
	{
		rl_clear_history();
		write(1, "exit\n", 5);
		return (0);
	}
	i = 0;
	while (ft_isspace(user_input[i]) == 1)
		i++;
	if (ft_strncmp(user_input + i, "exit", 4) == 0)
	{
		while (ft_isspace(user_input[i + 4]) == 1)
			i++;
		if (user_input[i + 4] == '\0')
		{
			rl_clear_history();
			free(user_input);
			return (0);
		}
	}
	return (1);
}

int	cmd_prompt(t_env_ms *env_ll)
{
	char	*user_input;
	int		ret;

	while (1)
	{
		g_signal_status = 0;
		signal(SIGINT, handler_first_readline);
		user_input = readline("minishell$ ");
		if (g_signal_status == 130)
			set_exit_code(env_ll, 130);
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
		if (user_input && launch_program(user_input, env_ll) == -1)
			return (-1);
	}
	return (3);
}
