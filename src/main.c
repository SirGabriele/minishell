/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:08:38 by kbrousse          #+#    #+#             */
/*   Updated: 2022/10/03 10:32:13 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, SIG_IGN);
	cmd_prompt();
}

/*main:

-Fonction signal
-Fonction cmd_prompt
-parsing / gestion d'erreurs
-interpretation commande (pipex)
-Variables d'environnement
-$? status derniere commande

*/
