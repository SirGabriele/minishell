/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:41:45 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:41:47 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	nb_redir_left(t_token_ms *tokens)
{
	t_token_ms	*tmp_tokens;

	tmp_tokens = tokens;
	while (tmp_tokens)
	{
		if (is_token_type_a_redir(tmp_tokens->type))
			return (1);
		tmp_tokens = tmp_tokens->next;
	}
	return (0);
}

static t_redir_ms	*ft_lstnew_redir(void)
{
	t_redir_ms	*lst;

	lst = malloc(sizeof(t_redir_ms));
	if (!lst)
	{
		perror(NULL);
		return (NULL);
	}
	lst->file_name = NULL;
	lst->mode = TOK_NULL;
	lst->next = NULL;
	return (lst);
}

static t_redir_ms	*get_infos(t_redir_ms *first_redir, \
	t_token_ms *tokens)
{
	int	len_content;

	len_content = ft_strlen(tokens->next->content);
	first_redir->file_name = malloc((len_content + 1) * sizeof(char));
	if (!first_redir->file_name)
		return (NULL);
	ft_strcpy(first_redir->file_name, tokens->next->content);
	first_redir->mode = tokens->type;
	if (nb_redir_left(tokens->next->next))
	{
		first_redir->next = ft_lstnew_redir();
		if (!first_redir)
			return (NULL);
		first_redir = first_redir->next;
	}
	else
		first_redir->next = NULL;
	return (first_redir);
}

/************************************************************/
/*															*/
/*	Gets every redirections and stocks them in a list		*/
/*	containing modes and files								*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	link									*/
/*															*/
/*	Return:													*/
/*		first_redir	-	linked list of redirections			*/
/*															*/
/************************************************************/

t_redir_ms	*get_redirections_list(t_token_ms *tokens)
{
	t_redir_ms	*first_redir;
	t_redir_ms	*tmp_first_redir;

	first_redir = ft_lstnew_redir();
	if (!first_redir)
		return (NULL);
	tmp_first_redir = first_redir;
	while (tokens)
	{
		if (is_token_type_a_redir(tokens->type))
		{
			tmp_first_redir = get_infos(tmp_first_redir, tokens);
			if (!tmp_first_redir)
				return (NULL);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (first_redir);
}
