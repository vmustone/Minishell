
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:33:44 by vmustone          #+#    #+#             */
/*   Updated: 2023/06/14 21:24:01 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static int	is_str_number(char *str)
{
	int i;

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

void	ft_exit(char **argv)
{
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("too many arguments", 2);
	}
	else if (argv[1] && is_str_number(argv[1]) == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}