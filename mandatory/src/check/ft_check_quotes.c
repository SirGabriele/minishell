/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:05:05 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 23:29:01 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_quote_closed(const char *user_input, int i)
{
	int	j;

	j = i + 1;
	while (user_input[j] != user_input[i] && user_input[j] != '\0')
		j++;
	if (user_input[j] == '\0')
		return (-1);
	return (0);
}

/************************************************************/
/*															*/
/*	Detects if an isolated quote is in the line				*/
/*															*/
/*	Parameters:												*/
/*		user_input	-	line from the terminal         		*/
/*															*/
/*	Return:													*/
/*		0	-	no isolated quote is detected				*/
/*		1	-	an isolated quote is detected and 			*/
/*				highlighted									*/
/*															*/
/************************************************************/
int	ft_check_isolated_quotes(const char *user_input, t_env_ms *env_ll)
{
	char	*err_msg;
	int		i;
	char	save;

	err_msg = "minishell: syntax error: isolated quote detected\n";
	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '\"' || user_input[i] == '\'')
		{
			save = user_input[i];
			if (is_quote_closed(user_input, i) == -1)
			{
				write(2, err_msg, ft_strlen(err_msg));
				highlight_syntax_error(user_input, i, i);
				set_exit_code(env_ll, 1);
				return (-1);
			}
			i++;
			while (user_input[i] != save)
				i++;
		}
		i++;
	}
	return (0);
}
