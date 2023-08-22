/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:13:30 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 17:25:09 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_variable_char(char c)
{
	if (!ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	counter_dollar(int i, char *str, int *count)
{
	i++;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '<'
		&& str[i] != '>' && str[i] != '|' && str[i] != '\"'
		&& str[i] != '\'' && str[i] != '$' && is_valid_variable_char(str[i]))
	{
		i++;
	}
	(*count)++;
	return (i);
}

int	counter_normal_word(int i, char *str, int *count)
{
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '<'
		&& str[i] != '>' && str[i] != '|' && str[i] != '\"'
		&& str[i] != '\'' && str[i] != '$')
	{
		i++;
	}
	(*count)++;
	return (i);
}
