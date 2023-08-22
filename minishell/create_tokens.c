/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:06:18 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 18:11:22 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_lib(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (T_PIPE);
	else if (!ft_strcmp(str, ">"))
		return (T_ARROW_R);
	else if (!ft_strcmp(str, "<"))
		return (T_ARROW_L);
	else if (!ft_strcmp(str, ">>"))
		return (T_ARROW_R_2);
	else if (!ft_strcmp(str, "<<"))
		return (T_ARROW_L_2);
	else if (identify_variable(str))
		return (T_VARIABLE);
	else
		return (T_WORD);
}

int	is_redirect_or_file(char *str, int last_run)
{
	static int	looking_for_file;

	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>")
		|| !ft_strcmp(str, "<<"))
	{
		if (last_run == 1)
			return (0);
		looking_for_file = 1;
		return (1);
	}
	if (looking_for_file == 1)
	{
		looking_for_file = 0;
		return (1);
	}
	else
		return (0);
}

int	define_token_type(char *str, int last_run)
{
	static int	is_command;

	if (is_quoted(str) == 1)
	{
		if (last_run == 1)
			is_command = 0;
		return (T_WORD);
	}
	if (is_command == 0)
	{
		if (is_redirect_or_file(str, last_run) == 1)
			return (type_lib(str));
		if (last_run != 1)
			is_command = 1;
		return (T_COMMAND);
	}
	else
	{
		if (!ft_strcmp(str, "|"))
			is_command = 0;
		if (last_run == 1)
			is_command = 0;
		return (type_lib(str));
	}
}

int	last_time(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i == 1)
		return (1);
	else
		return (0);
}

t_tokens	*create_tokens(char **splitted_input, t_shell *shell)
{
	t_tokens			*head;
	t_tokens			*node;

	head = NULL;
	while (*splitted_input)
	{
		node = oh_my_malloc(sizeof(t_tokens), shell->allocs);
		if (!node)
		{
			ft_error("malloc error");
			return (NULL);
		}
		if (set_node_values(splitted_input, &node, shell))
			return (NULL);
		if (!head)
			head = node;
		else
			shell->tokens->next = node;
		shell->tokens = node;
		splitted_input++;
	}
	return (head);
}
