/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_to_expand_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:58 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:08:09 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	*get_key_to_expand(char *content)
{
	char	*key_to_expand;
	int		j;

	j = 0;
	while (ft_isdigit(content[j]) != 1
		&& content[j] != ' ' && content[j] != '\"'
		&& content[j] != '$' && content[j] != '\0'
		&& content[j] != '\'' && content[j] != '='
		&& content[j] != '-' && content[j] != '?')
		j++;
	if (content[j] == '?' || content[j] == '0')
		j++;
	key_to_expand = ft_strndup(content, j);
	if (key_to_expand == NULL)
	{
		free(content);
		perror(NULL);
		return (NULL);
	}
	return (key_to_expand);
}
