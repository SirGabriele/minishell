/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:47:05 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 15:53:24 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void	update_data(t_env_ms *old_pwd, t_env_ms *pwd,
	t_env_ms *last_link)
{
	char	*post_cd_pwd;

	post_cd_pwd = getcwd(NULL, 0);
	if (old_pwd)
		free(old_pwd->value);
	if (pwd != NULL)
		old_pwd->value = pwd->value;
	else
		old_pwd->value = NULL;
	if (pwd == NULL)
	{
		last_link->next = lstnew_env_link();
		last_link->next->key = ft_strdup("PWD");
		last_link->next->value = ft_strdup(post_cd_pwd);
		last_link->next->next = NULL;
		pwd = last_link->next;
	}
	else
		pwd->value = ft_strdup(post_cd_pwd);
	free(post_cd_pwd);
}

static void	change_pwd_and_oldpwd(t_env_ms *env_ll)
{
	t_env_ms	*old_pwd;
	t_env_ms	*pwd;

	old_pwd = NULL;
	pwd = NULL;
	while (env_ll != NULL)
	{
		if (ft_strcmp(env_ll->key, "OLDPWD") == 0)
			old_pwd = env_ll;
		else if (ft_strcmp(env_ll->key, "PWD") == 0)
			pwd = env_ll;
		if (env_ll->next)
			env_ll = env_ll->next;
		else
			break ;
	}
	update_data(old_pwd, pwd, env_ll);
}

static int	change_directory(char *content, t_env_ms *env_ll)
{
	char	*error;
	int		exit_status;

	error = ft_strjoin("minishell: cd: ", content);
	if (!error)
		perror(NULL);
	exit_status = chdir(content);
	if (exit_status)
	{
		perror(error);
		free(error);
		return (1);
	}
	change_pwd_and_oldpwd(env_ll);
	free(error);
	return (0);
}

int	ft_cd(char **content, t_env_ms *env_ll)
{
	int	nb_args;
	int	ret;

	ret = 0;
	nb_args = count_args(content);
	if (nb_args == 1)
		ret = change_directory(content[0], env_ll);
	else
	{
		if (!nb_args)
			ft_putstr_fd("minishell: cd: missing relative/absolute path\n", 2);
		else
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (ret);
}
