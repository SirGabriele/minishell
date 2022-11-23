/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:08:38 by kbrousse          #+#    #+#             */
/*   Updated: 2022/11/23 17:58:34 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_node_ms	*root;
	t_env_ms	*env_copy;
	int			ret;

	env_copy = convert_double_env_into_ll(env);
	root = malloc(sizeof(t_node_ms));
		return (1);
	if (env_copy == NULL || root == NULL)
		return (1);
	init_tree_struct(node);
	(void)argc;
	(void)argv;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, SIG_IGN);
	ret = cmd_prompt(root, env_copy);
	free_program(root, env_copy);//add free_env_copy;
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
