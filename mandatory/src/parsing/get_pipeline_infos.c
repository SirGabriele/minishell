/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipeline_infos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:41:37 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/21 00:27:32 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_there_a_command(t_token_ms *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOK_STRING)
			return (1);
		else if (is_token_type_a_redir(tokens->type))
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (0);
}

static char	**malloc_pipelines(t_token_ms *tokens)
{
	char		**pipelines;
	int			nb_tokens_left;

	nb_tokens_left = count_nb_of_tokens_left(tokens);
	pipelines = malloc((nb_tokens_left + 1) * sizeof(char *));
	if (!pipelines)
		return (NULL);
	return (pipelines);
}

static char	**get_pipeline(t_token_ms *tokens)
{
	char		**pipelines;
	int			i;

	pipelines = malloc_pipelines(tokens);
	if (!pipelines)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (!is_token_type_a_redir(tokens->type))
		{
			pipelines[i] = ft_strdup(tokens->content);
			if (!pipelines[i])
				return (NULL);
			i++;
		}
		else
			tokens = tokens->next;
		tokens = tokens->next;
	}
	pipelines[i] = NULL;
	return (pipelines);
}

/************************************************************/
/*															*/
/*	Gets infos about redirections and gets the command		*/
/*															*/
/*	Parameters:												*/
/*		tokens		-	link								*/
/*		shell		-	what is command in					*/
/*		operators	-	the last two operators of 			*/
/*						the command line					*/
/*															*/
/*	Return:													*/
/*		root	-	edited binary_tree						*/
/*															*/
/************************************************************/

t_node_ms	*get_pipeline_infos(t_node_ms *root, t_token_ms *tokens, \
	t_enum_token *operators)
{
	root = get_redirections_infos(root, tokens, operators);
	if (!root)
		return (NULL);
	if (is_there_a_command(tokens))
	{
		root->content = get_pipeline(tokens);
		if (!root->content)
		{
			free_redirs_list(root->first_redir);
			free_redirs_infos(root);
			free(root);
			return (NULL);
		}
	}
	return (root);
}
