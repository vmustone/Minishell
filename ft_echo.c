/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:21:18 by vmustone          #+#    #+#             */
/*   Updated: 2023/08/20 15:57:55 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_args(char **argv)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	j = 0;
	newline = 0;
	if (argv[i][j] == '-')
		j++;
	if (argv[i][j] == '\0')
	{
		newline = 1;
		return (newline);
	}
	while (argv[i][j] == 'n')
		j++;
	if (argv[i][j] != 'n' && argv[i][j] != '\0')
		newline = 1;
	return (newline);
}

int	ft_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	if (!argv[i] || (argv[i][0] == '\0' && argv[i + 1] == NULL))
	{
		printf("\n");
		return (0);
	}
	newline = process_args(argv);
	if (newline == 0)
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1] && argv[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (newline == 1)
		printf("\n");
	return (0);
}
