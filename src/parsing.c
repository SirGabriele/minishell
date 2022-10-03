/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:33:12 by jsauvain          #+#    #+#             */
/*   Updated: 2022/10/03 11:12:52 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *line_read)
{
	int		i;
	int		s;
	int		d;

	i = 0;
	s = 0;
	d = 0;
	while (line_read[i] == ''' && line_read[i] == '"')
	{
		if (line_read[i] == ''')
			s++;
		else if (line_read[i] == '"')
			d++;
		i++;
	}
	return ();
}

int	parsing_quotes(char *line_read)
{
	int		i;
	int		d;

	i = count_quotes(line_read);
	q = i;
	while (line_read[i] != ''' && line_read[i] != '"')
		i++;
	while (line_read[i] == ''' && line_read[i] == '"')
	{
		if (line_read[i] == ''')
			s++;
		else if (line_read[i] == '"')
			d++;
		i++;
	}
	if (s % 2 || d % 2)
	{
		ft_printf("Missing quotes.\n");
		exit(1);
	}
	return (
}

char	*get_cmd_parsed(char *line_read)
{
	char	*duplicate;
	return (line_read + i);
}

char	**parsing(char *line_read)
{
	int	i;

	i = 0;
	line_read = get_cmd_parsed(line_read);
}
