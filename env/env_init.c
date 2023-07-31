/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:25:39 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/28 15:38:36 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

void	free_env(t_env *env)
{
    while (env)
	{
        free(env->data);
        free(env);
        env = env->next;
    }
	free(env);
}

int	env_size(t_env *env)
{
	int	len;

	len = 0;
	while (env && env->next)
	{
		if (env->data)
		{
			len = len + ft_strlen(env->data);
			len++;
		}
		env = env->next;
	}
	return (len);
}

char	*str_env(t_env *env)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = malloc(sizeof(char) * env_size(env) + 1);
	if (!str)
		return (NULL);
	while (env && env->next)
	{
		if (env->data)
		{
			j = 0;
			while (env->data[j])
			{
				str[i] = env->data[j];
				i++;
				j++;
			}
		}
		if (env->next->next)
			str[i++] = '\n';
		env = env->next;
	}
	str[i] = '\n';
	return (str);
}

int	env_init(t_data *data, char **env_array)
{
	t_env	*env;
	t_env	*new;

	int	i;

	i = 1;
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->data = ft_strdup(env_array[0]);
	env->next = NULL;
	data->env = env;
	while (env_array && env_array[0] && env_array[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->data = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}