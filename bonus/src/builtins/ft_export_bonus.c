/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:47:33 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 15:48:17 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	is_invalid_identifier(char *content)
{
	int	i;

	i = 0;
	while (content[i] && content[i] != '=')
	{
		if (content[i] == '~' || content[i] == '#'
			|| content[i] == '{' || content[i] == '[' || content[i] == '-'
			|| content[i] == '^' || content[i] == '@' || content[i] == ']'
			|| content[i] == '}' || content[i] == '*' || content[i] == '%'
			|| content[i] == '!' || content[i] == ':' || content[i] == '/'
			|| content[i] == '.' || content[i] == '?' || content[i] == ','
			|| (content[i] == '+' && content[i + 1] != '='))
			return (1);
		i++;
	}
	return (0);
}

static void	print_line(t_env_ms *env_cpy, int fd)
{
	if (env_cpy->key[0] != '?' && env_cpy->key[0] != '_')
	{
		ft_printf_fd(fd, "declare -x %s", env_cpy->key);
		if (env_cpy->value != NULL)
			ft_printf_fd(fd, "=\"%s\"", env_cpy->value);
		write(fd, "\n", 1);
	}
}

static int	process_variable(char *content, t_env_ms *env_ll)
{
	int	ret;

	if (is_invalid_identifier(content))
	{
		ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n",
			content);
		return (1);
	}
	ret = check_errors_env_format(content);
	if (ret != 1)
	{
		if (set_values_export(content, env_ll) != 0 || env_ll == NULL)
		{
			ft_putstr_fd("Error occured in ft_export.c\n", 2);
			return (1);
		}
	}
	return (ret);
}

static void	print_all_environment(t_env_ms *env_ll, char *outfile,
	t_enum_token outfile_mode, t_pipes_ms *pipes)
{
	t_env_ms	*env_cpy;
	int			fd;

	if (outfile_mode == TOK_PIPE)
		fd = pipes->after[1];
	else if (outfile == NULL || outfile_mode == TOK_NULL)
		fd = 1;
	else if (outfile != NULL && outfile_mode == TOK_TRUNC)
		fd = open(outfile, O_WRONLY | O_TRUNC);
	else if (outfile != NULL && outfile_mode == TOK_APPEND)
		fd = open(outfile, O_WRONLY | O_APPEND);
	sort_env_ll(env_ll);
	env_cpy = env_ll;
	while (env_cpy != NULL)
	{
		print_line(env_cpy, fd);
		env_cpy = env_cpy->next;
	}
	if (outfile != NULL)
		close(fd);
}

int	ft_export(t_node_ms *node, t_env_ms *env_ll, t_pipes_ms *pipes)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if (!node->content[1])
	{
		print_all_environment(env_ll, node->outfile, node->outfile_mode, pipes);
		return (0);
	}
	while (node->content[i] != NULL)
	{
		ret = process_variable(node->content[i], env_ll);
		i++;
	}
	return (ret);
}
