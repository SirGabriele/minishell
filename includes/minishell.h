/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:11:31 by kbrousse          #+#    #+#             */
/*   Updated: 2022/09/30 11:13:14 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
/////////////////////////
//	readline
/////////////////////////

# define FALSE -1

typedef struct s_context_mini
{
	int	single_quote;
	int	double_quote;
}	t_context_mini;

void	echo_requested(char **argv, char **env);

#endif
