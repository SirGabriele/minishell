/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:08:38 by kbrousse          #+#    #+#             */
/*   Updated: 2022/10/05 11:08:08 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, SIG_IGN);
	cmd_prompt(env);
}

/*main:

-Fonction signal
-Fonction cmd_prompt
-parsing / gestion d'erreurs
-interpretation commande (pipex)
-Variables d'environnement
-$? status derniere commande

*/
