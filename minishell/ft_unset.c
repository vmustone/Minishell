/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:34:01 by vmustone          #+#    #+#             */
/*   Updated: 2023/08/21 15:54:26 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_')
		return (0);
	else if (str[i] == '=')
		return (1);
	else if (ft_isdigit(str[i]) == 0)
		return (1);
	else if (ft_isalpha(str[i]) == 0 || ft_isalpha(*str) == 1)
		return (0);
	return (1);
}

static void	remove_env_variable(t_env **env, t_env *prev, t_env *current)
{
	if (prev)
		prev->next = current->next;
	else
		*env = current->next;
	free(current->data);
	free(current);
}

static int	unset_single_variable(char *variable, t_env **env)
{
	t_env	*prev;
	char	*tmp;
	t_env	*current;

	prev = NULL;
	tmp = ft_strjoin(variable, "=");
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->data, tmp, ft_strlen(tmp)) == 0)
		{
			remove_env_variable(env, prev, current);
			free(tmp);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	free(tmp);
	return (0);
}

int	ft_unset(char **argv, t_env *env)
{
	int	i;

	i = 1;
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		if (!unset_single_variable(argv[i], &env))
			printf("MINISHELL: unset: '%s': not a valid identifier\n", argv[i]);
		i++;
	}
	return (0);
}
