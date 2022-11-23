#include "../includes/minishell.h"

static void	free_user_input_and_set_to_null(char *user_input)
{
	free(user_input);
	user_input = NULL;
}

static int	handle_prompt(char *user_input)
{
	if (!user_input)
	{
		rl_clear_history();
		write(1, "exit\n", 5);
		return (-1);
	}
	if (ft_strncmp(user_input, "exit", 4) == 0)
	{
		rl_clear_history();
		free_user_input_and_set_to_null(user_input);
		return (-1);
	}
	if (ft_strlen(user_input) > 0)
		add_history(user_input);
	return (0);
}

int	cmd_prompt(t_context_ms *context, char **env)
{
	char	*user_input;

	(void)env;
	while (1)
	{
		user_input = readline("minishell> ");
		if (handle_prompt(user_input) == -1)
			return (0);
		if (launch_program(context, &user_input) == -1)
			free_user_input_and_set_to_null(user_input);
		else
		{
//			ft_printf("%s\n", user_input);//A VIRER
			free_user_input_and_set_to_null(user_input);
		}
	}
	return (0);
}
