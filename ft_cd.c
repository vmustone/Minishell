/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:22:49 by villemuston       #+#    #+#             */
/*   Updated: 2023/08/21 15:56:04 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_env *env, char *str, int len)
{
	char	*pwd;

	while (env && env->next)
	{
		if (ft_strncmp(env->data, str, len) == 0)
		{
			pwd = ft_strdup(env->data + len + 1);
			return (pwd);
		}
		env = env->next;
	}
	return (NULL);
}

static void	update_env(const char *name, const char *value, t_env *env)
{
	char	*new_data;
	char	*temp;

	while (env)
	{
		if (ft_strncmp(env->data, name, ft_strlen(name)) == 0)
		{
			new_data = ft_strjoin(name, "");
			temp = ft_strjoin(new_data, value);
			free(new_data);
			if (temp)
				env->data = temp;
			return ;
		}
		env = env->next;
	}
}

static int	update_pwd(t_env *env)
{
	char	current_dir[PATH_MAX];
	char	*pwd;
	char	*oldpwd;

	if (getcwd(current_dir, PATH_MAX) == NULL)
		return (1);
	oldpwd = get_path(env, "PWD", 3);
	if (oldpwd)
	{
		update_env("OLDPWD=", oldpwd, env);
		free(oldpwd);
	}
	pwd = current_dir;
	update_env("PWD=", pwd, env);
	return (0);
}

int	ft_cd(char **argv, t_env *env)
{
	int		ret;
	char	*home_path;

	ret = 0;
	if (!argv[1])
	{
		home_path = get_path(env, "HOME", 4);
		if (!home_path)
		{
			ft_putendl_fd("MINISHELL: cd: HOME not set", 2);
			return (1);
		}
		ret = chdir(home_path);
		free(home_path);
	}
	else
		ret = chdir(argv[1]);
	if (ret != 0)
	{
		perror("MINISHELL: cd");
		return (1);
	}
	update_pwd(env);
	return (0);
}
