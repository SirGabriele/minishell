#include "../../includes/minishell.h"

static int	is_all_digit(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '-' || content[i] == '+')
		i++;
	while (content[i] != '\0')
	{
		if (ft_isdigit(content[i]) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}

static void	exit_program_failure(t_env_ms *env_ll, t_pipes_ms *pipes)
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

int	ft_exit(char **content, t_env_ms *env_ll, t_pipes_ms *pipes)
{
	int	nb_args;

	nb_args = count_args(content);
	if (nb_args == 1 && is_all_digit(content[0]) == 0
		&& is_exit_value_out_of_range(content[0]) == 0)
		exit_program_success(content[0], env_ll, pipes);
	else if (nb_args == 1 && (is_all_digit(content[0]) == 1
			|| is_exit_value_out_of_range(content[0]) == 1))
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			content[0]);
		exit_program_failure(env_ll, pipes);
	}
	else if (nb_args > 1 && (is_all_digit(content[0]) == 1
			|| is_exit_value_out_of_range(content[0]) == 1))
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			content[0]);
		exit_program_failure(env_ll, pipes);
	}
	else if (nb_args > 1 && is_all_digit(content[0]) == 0
		&& is_exit_value_out_of_range(content[0]) == 0)
	{
		ft_printf_fd(1, "exit\n");
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
	}
	return (1);
}
