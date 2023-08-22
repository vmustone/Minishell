/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:53:36 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/17 19:38:57 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	while (env)
	{
		free (env->data);
		free (env);
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
				str[i++] = env->data[j++];
			}
		}
		if (env->next->next)
			str[i++] = '\n';
		env = env->next;
	}
	str[i] = '\n';
	return (str);
}
