#include "../../includes/minishell.h"

static int	is_invalid_identifier(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '~' || content[i] == '#'
			|| content[i] == '{' || content[i] == '[' || content[i] == '-'
			|| content[i] == '^' || content[i] == '@' || content[i] == ']'
			|| content[i] == '}' || content[i] == '*' || content[i] == '%'
			|| content[i] == '!' || content[i] == ':' || content[i] == '/'
			|| content[i] == '.' || content[i] == '?' || content[i] == ',')
			return (1);
		i++;
	}
	return (0);
}

static int	process_variable(char *content, t_env_ms **env_ll)
{
	int	ret;

	if (is_invalid_identifier(content))
	{
		ft_printf_fd(2, "minishell: export: %s: not a valid indetifier\n", 
			content);
		set_exit_code(*env_ll, 1);
		return (1);
	}
	ret = check_errors_env_format(content);
	if (ret != 1)
	{
		*env_ll = set_values_export(content, *env_ll);
		if (*env_ll == NULL)
		{
			ft_putstr_fd("Error occured in ft_export.c\n", 2);
			return (1);
		}
	}
	return (ret);
}

static void	sort_env_ll(t_env_ms *env_ll)
{
	t_env_ms	*current;
	t_env_ms	*next;
	char		*temp_key;
	char		*temp_value;

	current = env_ll;
	while (current->next != NULL)
	{
		next = current->next;
		if (ft_strcmp(current->key, next->key) > 0)
		{
			temp_key = next->key;
			temp_value = next->value;
			next->key = current->key;
			next->value = current->value;
			current->key = temp_key;
			current->value = temp_value;
			current = env_ll;
		}
		else
		{
			current = current->next;
			next = current->next;
		}
	}
}

static void	print_all_environment(t_env_ms *env_ll, char *outfile,
	int outfile_mode)
{
	t_env_ms	*env_cpy;
	int			fd;

	if (outfile == NULL && outfile_mode == TOK_NULL)
		fd = 1;
	else if (outfile != NULL && outfile_mode == TOK_TRUNC)
		fd = open(outfile, O_WRONLY | O_TRUNC);
	else if (outfile != NULL && outfile_mode == TOK_APPEND)
		fd = open(outfile, O_WRONLY | O_APPEND);
	sort_env_ll(env_ll);
	env_cpy = env_ll;
	while (env_cpy != NULL)
	{
		if (env_cpy->key[0] != '?' && env_cpy->key[0] != '_')
		{
			ft_printf_fd(fd, "declare -x %s", env_cpy->key);
			if (env_cpy->value)
				ft_printf_fd(fd, "=\"%s\"", env_cpy->value);
			write(fd, "\n", 1);
		}
		env_cpy = env_cpy->next;
	}
	if (outfile != NULL)
		close(fd);
}

int	ft_export(char **content, t_env_ms **env_ll, char *outfile,
	int outfile_mode)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if (!content[1])
	{
		print_all_environment(*env_ll, outfile, outfile_mode);
		set_exit_code(*env_ll, 0);
		return (0);
	}
	if (content[1][0] == '-')
	{
		ft_printf_fd(2, "minishell: export: %s: invalid option\nminishell does"
			" not take any option\n", content[1]);
		set_exit_code(*env_ll, 2);
		return (2);
	}
	while (content[i] != NULL)
	{
		ret = process_variable(content[i], env_ll);
		i++;
	}
	return (ret);
}
