/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:01 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/18 16:01:56 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int	open_quote(char *str, int i)
{
	char	temp;
	int		count;

	count = 1;
	temp = str[i++];
	if (str[i] == temp && str[i + 1] != temp)
		return (i + 1);
	while (str[i] == temp)
	{
		count++;
		i++;
	}
	while (str[i] != temp && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		ft_error("minishell: unexpected EOF while looking for matching `\"'");
		return (-1);
	}
	else
		return (i + count);
}
