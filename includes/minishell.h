/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:11:31 by kbrousse          #+#    #+#             */
/*   Updated: 2022/10/04 10:26:08 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

//prompt.c
void	ft_signal(int sig);
void	cmd_prompt(void);

//builtins.c
int		echo(char **str, char *options);

//parsing.c
char	*get_cmd_parsed(char *line_read);
char	*parsing(char *line_read);

# define FALSE -1

typedef struct s_context_mini
{
	int	single_quote;
	int	double_quote;
}	t_context_mini;

void	echo_requested(char **argv, char **env);

#endif
