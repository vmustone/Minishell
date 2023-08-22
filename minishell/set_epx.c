/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_epx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:18:57 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 17:19:14 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (shell_ft_substr(str, i + 1, ft_strlen(str) - i, shell->allocs));
}

int	check_env_cc(char *str, t_env *env, t_shell *shell)
{
	while (env)
	{
		if (ft_strcmp(str, get_value(env->data, shell)) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

char	**replace_arg_vector(char **old, char *to_replcae_with,
		int index_to_replace, t_shell *shell)
{
	int		i;
	char	**new;

	i = 0;
	while (old[i])
		i++;
	i--;
	new = (char **)oh_my_malloc(sizeof(char *) * (i + 1), shell->allocs);
	new[i] = NULL;
	i--;
	while (i >= 0)
	{
		if (i == index_to_replace)
			new[i] = to_replcae_with;
		else
			new[i] = old[i];
		i--;
	}
	return (new);
}

char	**set_expansion(t_exec *exec, t_shell *shell)
{
	int		i;
	char	*new_arg;
	int		rep;

	i = 0;
	while (exec->argv[i])
	{
		if (exec->argv[i + 1] && exec->argv[i + 1][0] == '='
			&& check_env_cc(exec->argv[i], shell->env, shell))
		{
			new_arg = shell_ft_strjoin(exec->argv[i],
					exec->argv[i + 1], shell);
			rep = i;
			return (replace_arg_vector(exec->argv, new_arg, rep, shell));
		}
		i++;
	}
	return (exec->argv);
}
