/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:30:54 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/20 16:27:21 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	counter(char *str, int count, int i)
{
	while (str[i] != '\0')
	{
		i = skip_spaces(str, i);
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = open_quote(str, i);
			count++;
		}
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			i = pipes_and_redirections(str, i);
			count++;
		}
		else if (str[i] == '$')
			i = counter_dollar(i, str, &count);
		else if (str[i] != '\0')
			i = counter_normal_word(i, str, &count);
		if (i == -1)
			return (-1);
	}
	return (count);
}

char	**make_splitted_input(char *str, int count, char **new, t_shell *shell)
{
	int		i;
	int		j;
	int		k;

	init_split_variables(&i, &j, &k);
	while (j < count)
	{
		i = skip_spaces(str, i);
		if (str[i] == '\'' || str[i] == '\"')
			new[j++] = quote_str(shell, &k, &i, str);
		else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			new[j++] = pipe_rdr_str(shell, &k, &i, str);
		else if (str[i] == '$')
			new[j++] = dollar_str(shell, &k, &i, str);
		else if (str[i] != '\0')
		{
			find_word_or_end(str, &i, &k);
			new[j++] = shell_ft_substr(str, k, i - k, shell->allocs);
		}
		if (new[j - 1] == NULL)
			return (NULL);
	}
	return (new);
}

char	**split_shell_input(char *str, t_shell *shell)
{
	int		count;
	char	**new;

	count = counter(str, 0, 0);
	if (count < 0)
		return (NULL);
	new = (char **)oh_my_malloc(sizeof(char *) * (count + 1), shell->allocs);
	if (!new)
		return (NULL);
	new[count] = NULL;
	new = make_splitted_input(str, count, new, shell);
	if (!new)
		return (NULL);
	return (new);
}
