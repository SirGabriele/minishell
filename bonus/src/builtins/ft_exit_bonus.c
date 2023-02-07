/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:47:16 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 15:47:17 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void	exit_program_failure(t_env_ms *env_ll,
	t_pipes_ms *pipes)
{
	close(pipes->before[0]);
	close(pipes->before[1]);
	close(pipes->after[0]);
	close(pipes->after[1]);
	free_binary_tree(pipes->tree_root);
	free_env_list(env_ll);
	free(pipes->children->pid_arr);
	free(pipes->children);
	free(pipes);
	exit(2);
}

static void	exit_program_success(char *content,
	t_env_ms *env_ll, t_pipes_ms *pipes)
{
	int	exit_code;

	exit_code = ft_atoi(content) % 256;
	close(pipes->before[0]);
	close(pipes->before[1]);
	close(pipes->after[0]);
	close(pipes->after[1]);
	free_binary_tree(pipes->tree_root);
	free_env_list(env_ll);
	free(pipes->children->pid_arr);
	free(pipes->children);
	free(pipes);
	exit(exit_code);
}

static void	more_than_one_argument(char **content, t_env_ms *env_ll,
	t_pipes_ms *pipes)
{
	if (is_all_digit(content[0]) == 1
		|| is_exit_value_out_of_range(content[0]) == 1)
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			content[0]);
		exit_program_failure(env_ll, pipes);
	}
	else if (is_all_digit(content[0]) == 0
		&& is_exit_value_out_of_range(content[0]) == 0)
	{
		ft_printf_fd(2, "exit\n");
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
	}
}

static void	only_one_argument(char **content, t_env_ms *env_ll,
	t_pipes_ms *pipes)
{
	if (is_all_digit(content[0]) == 0
		&& is_exit_value_out_of_range(content[0]) == 0)
		exit_program_success(content[0], env_ll, pipes);
	else if ((is_all_digit(content[0]) == 1
			|| is_exit_value_out_of_range(content[0]) == 1))
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			content[0]);
		exit_program_failure(env_ll, pipes);
	}
}

int	ft_exit(char **content, t_env_ms *env_ll, t_pipes_ms *pipes)
{
	int	nb_args;

	nb_args = count_args(content);
	if (nb_args == 1)
		only_one_argument(content, env_ll, pipes);
	else if (nb_args > 1)
		more_than_one_argument(content, env_ll, pipes);
	return (0);
}
