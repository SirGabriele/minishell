/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:40:33 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:40:33 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_binary_tree(t_node_ms *binary_tree)
{
	if (binary_tree)
	{
		free_double_arr(binary_tree->content);
		binary_tree->content = NULL;
		free_redirs_list(binary_tree->first_redir);
		binary_tree->first_redir = NULL;
		free(binary_tree->infile);
		binary_tree->infile = NULL;
		free(binary_tree->outfile);
		binary_tree->outfile = NULL;
		free_binary_tree(binary_tree->left);
		binary_tree->left = NULL;
		free_binary_tree(binary_tree->right);
		binary_tree->right = NULL;
		free(binary_tree);
		binary_tree = NULL;
	}
}

void	free_env_list(t_env_ms *env)
{
	t_env_ms	*tmp_env;

	while (env)
	{
		tmp_env = env->next;
		if (env->key != NULL)
			free(env->key);
		env->key = NULL;
		if (env->value != NULL)
			free(env->value);
		env->value = NULL;
		free(env);
		env = tmp_env;
	}
}
