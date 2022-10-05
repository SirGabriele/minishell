#include "../../includes/minishell.h"

static char	*replace_env_var(char *user_input, int i, char *env, int size)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_calloc(sizeof(char), i + 1);
	if (tmp == NULL)
		return (NULL); // CLEAR MEM
	tmp = ft_strncpy(tmp, user_input, i);
	while (*env != '=')
		env++;
	env++;
	tmp2 = ft_strjoin(tmp, env);
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin(tmp2, user_input + i + size);
	free(tmp2);
	tmp2 = NULL;
	return (tmp);
}

static char	*extract_env_variable(char *user_input, int i, char **env)
{
	char	*var;
	char	*tmp;
	int		j;
	int		k;

	j = 0;
	while (user_input[i + j] != ' ' && user_input[i + j] != '\"'
		&& user_input[i + j] != '$' && user_input[i + j] != '\0'
		&& user_input[i + j] != '\'')
		j++;
	var = ft_calloc(sizeof(char),  j + 1);
	if (var == NULL)
		return (NULL); //CLEAR MEM
	var = ft_strncpy(var, user_input + i, j);
	k = 0;
	while (env[k] != NULL)
	{
		if (ft_strncmp(env[k], var, j) == 0)
		{
			tmp = replace_env_var(user_input, i - 1, env[k], ft_strlen(var) + 1);
			break ;
		}
		k++;
	}
	if (env[k] == NULL)
	{
		ft_printf_error("Variable was not found\n");
		//CLER MEM;
	}
	return (tmp);
}

char	*manage_dollar_sign(char *user_input, char **env)
{
	int		i;

	i = 1;
	while (user_input[i] != '\"' && user_input[i] != '\0')
	{
		if (user_input[i] == '$')
			user_input = extract_env_variable(user_input, i + 1, env);
		i++;
	}
	return (user_input);
}
