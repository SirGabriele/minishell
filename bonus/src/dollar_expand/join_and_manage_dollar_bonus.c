/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_and_manage_dollar_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:50:27 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 23:37:55 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static char	*replace_dollar_digit(char *new_parsed, char *parsed, int i)
{
	if (parsed[i + 1] == '0')
	{
		new_parsed = ft_strjoin_free_first(new_parsed, "minishell");
		if (!new_parsed)
			return (NULL);
		new_parsed = \
			ft_strjoin_free_first(new_parsed, parsed + i + 2);
		return (new_parsed);
	}
	new_parsed = \
		ft_strjoin_free_first(new_parsed, parsed + i + 2);
	return (new_parsed);
}

static int	get_length_without_spaces(char *value)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (value[i] == ' ' && value[i])
		i++;
	while (value[i])
	{
		if (value[i] == ' ' && value[i + 1] != ' ')
			len++;
		if (value[i] == ' ')
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static char	*parse_spaces(char *value)
{
	char	*value_parsed;
	int		len_value_parsed;
	int		i;
	int		j;

	len_value_parsed = get_length_without_spaces(value);
	value_parsed = malloc((len_value_parsed + 1) * sizeof(char));
	if (!value_parsed)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i] == ' ' && value[i])
		i++;
	while (j < len_value_parsed)
	{
		if (value[i] == ' ' && value[i + 1] != ' ')
			value_parsed[j++] = value[i];
		if (value[i] == ' ')
			i++;
		else
			value_parsed[j++] = value[i++];
	}
	value_parsed[j] = '\0';
	return (value_parsed);
}

static char	*get_new_parsed(char *parsed, char *value, int i)
{
	char	*new_parsed;
	char	*value_parsed;

	if (value)
	{
		value_parsed = parse_spaces(value);
		if (!value_parsed)
			return (NULL);
	}
	else
		value_parsed = NULL;
	new_parsed = ft_strndup(parsed, i);
	if (!new_parsed)
	{
		free(value_parsed);
		return (NULL);
	}
	free(value_parsed);
	return (new_parsed);
}

/****************************************************************/
/*                                                     			*/
/*  Replaces dollar by env variable								*/
/*                                                     	 		*/
/*  Parameters:													*/
/*		env_var	-	env variable line							*/
/*		content	-	string with dollar							*/
/*		i		-	dollar index								*/
/*																*/
/*  Return:														*/
/*		content	-	the newly formed line						*/
/*																*/
/****************************************************************/

char	*join_and_manage_dollar(char *parsed, char *value, int key_len, int i)
{
	char	*new_parsed;

	new_parsed = get_new_parsed(parsed, value, i);
	if (value && new_parsed)
	{
		new_parsed = ft_strjoin_free_first(new_parsed, value);
		if (!new_parsed)
			return (NULL);
		new_parsed = \
			ft_strjoin_free_first(new_parsed, parsed + i + key_len + 1);
	}
	else if (!examine_dollar_conditions(parsed, i) && new_parsed)
	{
		new_parsed = \
			ft_strjoin_free_first(new_parsed, parsed + i + key_len + 1);
		return (new_parsed);
	}
	else if (examine_dollar_conditions(parsed, i) == 2 && new_parsed)
		new_parsed = replace_dollar_digit(new_parsed, parsed, i);
	return (new_parsed);
}
