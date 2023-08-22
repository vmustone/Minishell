/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:54:56 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 15:44:49 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i + 1] != '$')
				return (1);
			if (str[i] == '\'' && str[i + 1] == '$')
				return (1);
			if (str[i] == '\"' && str[i + 1] == '$')
				return (0);
		}
		i++;
	}
	return (0);
}

char	*remove_quotes_if_found(char *str, t_shell *shell, int i, int j)
{
	char	*ret;

	if (is_quoted(str) == 0)
		return (str);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			j++;
		i++;
	}
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

int	set_node_values(char **splitted_input, t_tokens **node, t_shell *shell)
{
	(*node)->data = set_data(*splitted_input, shell);
	if (!(*node)->data)
		return (1);
	(*node)->next = NULL;
	(*node)->type = define_token_type((*node)->data, last_time(splitted_input));
	if ((*node)->type == -1)
		return (1);
	if ((*node)->type == T_WORD)
	{
		(*node)->data = remove_quotes_if_found((*node)->data, shell, 0, 0);
		if (!(*node)->data)
			return (1);
	}
	return (0);
}
