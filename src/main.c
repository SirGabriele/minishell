/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:08:38 by kbrousse          #+#    #+#             */
/*   Updated: 2022/11/24 05:27:30 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_node_ms	*root;
	t_env_ms	*env_ll;
	int			ret;
	char		**env_arr;

	env_ll = convert_env_into_ll((const char **)env);//variables parasites ajoutées
	env_arr = convert_env_into_arr(env_ll);
//	print_env_arr(env_arr, env);
	root = malloc(sizeof(t_node_ms));
//	if (env_copy == NULL || root == NULL)
//		return (1);
	init_root_struct(root);
	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, ft_signal_user_input);
	signal(SIGQUIT, SIG_IGN);
	ret = 0;
	free(root);
//	ret = cmd_prompt(root, env_copy);
	free_double_arr(env_arr);
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
