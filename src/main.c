#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_node_ms	*root;
	t_env_ms	*env_ll;
//	char		**env_arr;
	int			ret;

	if (argc != 1 || argv[1] != NULL)
	{
		ft_putstr_fd("This program does not take any parameter\n", 2);
		return (1);
	}
	env_ll = convert_env_into_ll((const char **)env);//4 variables parasites ajoutées
//	env_arr = convert_env_into_arr(env_ll);
//	print_env_arr(env_arr, env);
	root = malloc(sizeof(t_node_ms));
	if (/*env_arr == NULL || */root == NULL)
		return (1);
	init_root_struct(root);
	signal(SIGINT, ft_signal_user_input);
	signal(SIGQUIT, SIG_IGN);
	ret = 0;
	ret = cmd_prompt(root, env_ll);
	free(root);
//	free_double_arr(env_arr);
	free_program(root, env_ll);
	return (ret);
}

/*main:

-Fonction signal
-Fonction cmd_prompt
-parsing / gestion d'erreurs
-interpretation commande (pipex)
-Variables d'environnement
-$? status derniere commande

*/
