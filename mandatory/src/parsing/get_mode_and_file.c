/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mode_and_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:41:34 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:41:35 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node_ms	*infile_context(t_node_ms *binary_tree, \
	t_redir_ms *first_redir)
{
	int	len_filename;

	len_filename = ft_strlen(first_redir->file_name);
	binary_tree->infile = malloc((len_filename + 1) * sizeof(char));
	if (!binary_tree->infile)
	{
		free(binary_tree);
		return (NULL);
	}
	ft_strcpy(binary_tree->infile, first_redir->file_name);
	binary_tree->infile_mode = first_redir->mode;
	return (binary_tree);
}

static t_node_ms	*outfile_context(t_node_ms *binary_tree, \
	t_redir_ms *first_redir)
{
	int	len_filename;

	len_filename = ft_strlen(first_redir->file_name);
	binary_tree->outfile = malloc((len_filename + 1) * sizeof(char));
	if (!binary_tree->outfile)
	{
		free(binary_tree);
		return (NULL);
	}
	ft_strcpy(binary_tree->outfile, first_redir->file_name);
	binary_tree->outfile_mode = first_redir->mode;
	return (binary_tree);
}

/***************************************/
/*        get_mode_and_file :          */
/*                                     */
/*   Get the mode of the redirection   */
/*   and the name of the file          */
/***************************************/

t_node_ms	*get_mode_and_file(t_node_ms *binary_tree, t_redir_ms *first_redir)
{
	if (first_redir->mode == TOK_INFILE || first_redir->mode == TOK_HEREDOC)
		binary_tree = infile_context(binary_tree, first_redir);
	else if (first_redir->mode == TOK_TRUNC || first_redir->mode == TOK_APPEND)
		binary_tree = outfile_context(binary_tree, first_redir);
	return (binary_tree);
}
