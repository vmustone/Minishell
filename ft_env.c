/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:36:02 by vmustone          #+#    #+#             */
/*   Updated: 2023/08/16 17:00:09 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_of_env(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

char	*env_name(char *new, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	add_env(char *data, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->data == NULL)
	{
		env->data = ft_strdup(data);
		return (0);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->data = ft_strdup(data);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

int	in_env(t_env *env, char *argv)
{
	char	name_of_var[4096];
	char	name_of_env[4096];

	env_name(name_of_var, argv);
	while (env && env->next)
	{
		env_name(name_of_env, env->data);
		if (ft_strcmp(name_of_var, name_of_env) == 0)
		{
			free(env->data);
			env->data = NULL;
			env->data = ft_strdup(argv);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		printf("%s\n", env->data);
		env = env->next;
	}
	if (env)
		printf("%s\n", env->data);
	return (0);
}
