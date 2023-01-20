/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:38:47 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:38:47 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char *outfile, t_enum_token outfile_mode, t_pipes_ms *pipes)
{
	char	*pwd;
	int		fd;

	if (outfile_mode == TOK_PIPE)
		fd = pipes->after[1];
	else if (outfile == NULL || outfile_mode == TOK_NULL)
		fd = 1;
	else if (outfile != NULL && outfile_mode == TOK_TRUNC)
		fd = open(outfile, O_WRONLY | O_TRUNC);
	else if (outfile != NULL && outfile_mode == TOK_APPEND)
		fd = open(outfile, O_WRONLY | O_APPEND);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror(NULL);
		return (1);
	}
	else
	{
		ft_printf_fd(fd, "%s\n", pwd);
		free(pwd);
	}
	if (outfile != NULL)
		close(fd);
	return (0);
}
