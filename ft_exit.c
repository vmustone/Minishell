/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:33:44 by vmustone          #+#    #+#             */
/*   Updated: 2023/08/22 15:23:30 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_str_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			i++;
		else
			return (1);
	}
	return (0);
}

void	ft_exit(char **argv, t_allocations *all)
{
	ft_putendl_fd("exit", 2);
	if (!argv[1])
		exit(g_exit_status);
	if (!is_str_number(argv[1]) && argv[2])
		ft_putendl_fd("MINISHELL: exit: too many arguments", 2);
	else if (argv[1] && is_str_number(argv[1]) == 1)
	{
		ft_putstr_fd("MINISHELL: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_exit_status = 255;
		exit (255);
	}
	else
	{
		g_exit_status = ft_atoi(argv[1]);
		oh_my_free(all);
		exit (g_exit_status);
	}
}
