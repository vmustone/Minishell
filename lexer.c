/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:55:47 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/09 00:12:13 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*lexer(char *input, t_shell *shell)
{
	t_tokens			*head;
	char				**splitted_input;

	splitted_input = split_shell_input(input, shell);
	if (!splitted_input)
		return (NULL);
	head = create_tokens(splitted_input, shell);
	if (!head)
		return (NULL);
	return (head);
}
