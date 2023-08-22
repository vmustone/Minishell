/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:22:32 by villemuston       #+#    #+#             */
/*   Updated: 2023/08/21 15:53:48 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort(char **argv, int len)
{
	int		i;
	int		j;
	char	*temp;

	j = 0;
	while (argv && j == 0)
	{
		j = 1;
		i = 0;
		while (i < len - 1)
		{
			if (ft_strcmp(argv[i], argv[i + 1]) > 0)
			{
				temp = argv[i];
				argv[i] = argv[i + 1];
				argv[i + 1] = temp;
				j = 0;
			}
			i++;
		}
		len--;
	}
}

static void	print_env(t_env *env)
{
	int		i;
	char	**list;
	char	*str;

	i = 0;
	str = str_env(env);
	list = ft_split(str, '\n');
	sort(list, len_of_env(list));
	while (list[i])
	{
		printf("declare -x ");
		printf("%s\n", list[i]);
		i++;
	}
	free(str);
	free(list);
}

static int	valid_env(char *src)
{
	int	i;
	int	check;

	i = 0;
	check = check_arg(src);
	if (check == 1)
	{
		printf("MINISHELL: export: '%s': not a valid identifier\n", src);
		return (1);
	}
	if (check == 0)
		i++;
	while (src[i] && src[i] != '=')
	{
		if (ft_isalnum(src[i]) == 1)
		{
			printf("MINISHELL: export: '%s': not a valid identifier\n", src);
			return (1);
		}
		i++;
	}
	if (src[i] != '=')
		return (2);
	return (0);
}

static int	validate_and_add(char *arg, t_env *env)
{
	int	error;
	int	new;

	error = valid_env(arg);
	if (error == 1)
	{
		g_exit_status = 1;
		return (1);
	}
	new = 0;
	if (error == 2)
		new = 1;
	else
		new = in_env(env, arg);
	if (new == 0)
	{
		if (error == 0)
			add_env(arg, env);
	}
	return (0);
}

int	ft_export(char **argv, t_env *env)
{
	int	i;

	i = 1;
	if (!argv[i])
		print_env(env);
	while (argv[i])
	{
		if (validate_and_add(argv[i], env) != 0)
			return (1);
		i++;
	}
	return (0);
}
