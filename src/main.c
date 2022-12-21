#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env_ms	*env_ll;

	if (argc != 1 || argv[1] != NULL)
	{
		ft_putstr_fd("This program does not take any parameter\n", 2);
		return (1);
	}
	env_ll = convert_env_arr_into_ll((const char **)env);//?=0 ajouté
	signal(SIGINT, ft_signal_user_input);
	signal(SIGQUIT, SIG_IGN);
	cmd_prompt(env_ll);
	//free_env_ll;
	return (3);
}
