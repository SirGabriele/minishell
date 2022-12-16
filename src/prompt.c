#include "../includes/minishell.h"

static void	free_user_input_and_set_to_null(char *user_input)
{
	free(user_input);
	user_input = NULL;
}

static int	check_nb_commands(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (!ft_isspace(user_input[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	handle_prompt(char *user_input)
{
	if (!user_input)
	{
		rl_clear_history();
		write(1, "exit\n", 5);
		return (-1);
	}
	else if (ft_strlen(user_input) > 0)
		add_history(user_input);
	return (0);
}

int	cmd_prompt(char **env)
{
	char	*user_input;

	while (1)
	{
		user_input = readline("minishell> ");
		if (handle_prompt(user_input) == -1)
			return (-1);
		if (check_nb_commands(user_input))
		{
			launch_program(&user_input, env);
			free_user_input_and_set_to_null(user_input);
		}
	}
	return (0);
}
