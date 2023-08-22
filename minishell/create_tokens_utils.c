/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:06:18 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/17 19:13:41 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_spaces(char *str, t_shell *shell, int i, int j)
{
	char	*ret;

	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			j++;
		i++;
	}
	if (j == 0)
		return (str);
	ret = oh_my_malloc(j + 1, shell->allocs);
	if (!ret)
		return (NULL);
	ret[j] = '\0';
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			ret[j++] = str[i];
		i++;
	}
	return (ret);
}

char	*remove_quotes(char *str, t_shell *shell, int i, int j)
{
	char	*ret;

	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			j++;
		i++;
	}
	if (j == 0)
		return (str);
	ret = oh_my_malloc(j + 1, shell->allocs);
	if (!ret)
		return (NULL);
	ret[j] = '\0';
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			ret[j++] = str[i];
		i++;
	}
	return (ret);
}

char	*set_data(char *str, t_shell *shell)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
		i++;
	while (str[j] != '$' && str[j] != '\0' && str[j] != '>'
		&& str[j] != '<' && str[j] != '|')
		j++;
	if (str[i] != '\0' && str[j] == '$')
		ret = remove_spaces(str, shell, 0, 0);
	else if (str[i] != '\0'
		&& (str[j] == '>' || str[j] == '<' || str[j] == '|'))
		return (shell_ft_strdup(str, shell->allocs));
	else
		ret = remove_quotes(str, shell, 0, 0);
	return (ret);
}

int	identify_variable(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$' && str[i + 1])
		return (1);
	return (0);
}
