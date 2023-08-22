/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:36:49 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/20 20:21:01 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_here_docs	*init_here_docs(t_shell *shell)
{
	t_here_docs	*ret;
	int			i;

	i = 0;
	ret = oh_my_malloc(sizeof(t_here_docs), shell->allocs);
	if (!ret)
	{
		shell_error("malloc error", 1, NULL);
		return (NULL);
	}
	else
	{
		ret->count = 0;
		ret->doc_name[49] = NULL;
		while (i < 49)
		{
			ret->doc_name[i] = shell_ft_strjoin("here_doc",
					shell_ft_itoa(i, shell), shell);
			i++;
		}
		return (ret);
	}
}

t_env	*env_init(char **env_array, t_allocations *allocs)
{
	t_env	*env;
	t_env	*head;
	int		i;

	i = 1;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->data = ft_strdup(env_array[0]);
	if (!env->data)
		shell_error("malloc error", 1, allocs);
	env->next = NULL;
	head = env;
	while (env_array[i])
	{
		env->next = malloc(sizeof(t_env));
		if (!env->next)
			shell_error("malloc error", 1, allocs);
		env = env->next;
		env->data = ft_strdup(env_array[i]);
		env->next = NULL;
		i++;
	}
	return (head);
}

t_allocations	*init_allocs(void)
{
	t_allocations	*ret;

	ret = malloc(sizeof(t_allocations));
	if (!ret)
	{
		shell_error("malloc error", 1, NULL);
		return (NULL);
	}
	else
	{
		ret->count = 0;
		return (ret);
	}
}
