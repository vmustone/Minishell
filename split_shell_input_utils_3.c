/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_input_utils_3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:26:33 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 16:10:30 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_str(t_shell *shell, int *k, int *i, char *str)
{
	char	*ret;

	*k = *i;
	*i = open_quote(str, *i);
	if (*i == -1)
		return (NULL);
	ret = shell_ft_substr(str, *k, *i - *k, shell->allocs);
	return (ret);
}

char	*pipe_rdr_str(t_shell *shell, int *k, int *i, char *str)
{
	char	*ret;

	*k = *i;
	*i = pipes_and_redirections(str, *i);
	if (*i == -1)
		return (NULL);
	ret = shell_ft_substr(str, *k, *i - *k, shell->allocs);
	return (ret);
}

void	find_word_or_end(char *str, int *i, int *k)
{
	*k = *i;
	while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '<'
		&& str[*i] != '>' && str[*i] != '|' && str[*i] != '\"'
		&& str[*i] != '\'' && str[*i] != '$')
		(*i)++;
}

char	*dollar_str(t_shell *shell, int *k, int *i, char *str)
{
	char	*ret;

	*k = *i;
	(*i)++;
	while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '<'
		&& str[*i] != '>' && str[*i] != '|' && str[*i] != '\"'
		&& str[*i] != '\'' && str[*i] != '$' && is_valid_variable_char(str[*i]))
		(*i)++;
	ret = shell_ft_substr(str, *k, *i - *k, shell->allocs);
	return (ret);
}

void	init_split_variables(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}
