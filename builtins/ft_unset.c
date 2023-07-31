/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:34:01 by vmustone          #+#    #+#             */
/*   Updated: 2023/07/25 16:51:26 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	ft_unset(char **argv, t_env *env)
{
	t_env	*prev;

	prev = NULL;
	if (!argv[1])
	{
		printf("Usage: unset Variable\n");
		return (1);
	}
	while (env)
	{
		if (ft_strcmp(env->data, argv[1]) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				env = env->next;
			free(env->data);
			free(env);
			return (0);
		}
		prev = env;
		env = env->next;
	}
	printf("unset: %s not found\n", argv[1]);
	return (1);
}
