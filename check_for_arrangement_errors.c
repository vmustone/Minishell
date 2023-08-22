/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_arrangement_errors.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:26:58 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/19 18:35:11 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	left(t_tokens *tokens)
{
	if (tokens->type == T_ARROW_L && (!tokens->next
			|| tokens->next->type == T_ARROW_R
			|| tokens->next->type == T_ARROW_R_2
			|| tokens->next->type == T_ARROW_L
			|| tokens->next->type == T_ARROW_L_2))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
		return (1);
	}
	if (tokens->type == T_ARROW_L_2 && (!tokens->next
			|| tokens->next->type == T_ARROW_R
			|| tokens->next->type == T_ARROW_R_2
			|| tokens->next->type == T_ARROW_L
			|| tokens->next->type == T_ARROW_L_2))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
		return (1);
	}
	return (0);
}

int	right(t_tokens *tokens)
{
	if (tokens->type == T_ARROW_R && (!tokens->next
			|| tokens->next->type == T_ARROW_R
			|| tokens->next->type == T_ARROW_R_2
			|| tokens->next->type == T_ARROW_L
			|| tokens->next->type == T_ARROW_L_2))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	if (tokens->type == T_ARROW_R_2 && (!tokens->next
			|| tokens->next->type == T_ARROW_R
			|| tokens->next->type == T_ARROW_R_2
			|| tokens->next->type == T_ARROW_L
			|| tokens->next->type == T_ARROW_L_2))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
		return (1);
	}
	return (0);
}

int	check_for_arrangement_errors(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->type == T_PIPE
			&& (!tokens->next || tokens->next->type == T_PIPE))
		{
			ft_putstr_fd("minishell: syntax error ", 2);
			ft_putstr_fd("near unexpected token `|'\n", 2);
			return (1);
		}
		if (right(tokens) || left(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
