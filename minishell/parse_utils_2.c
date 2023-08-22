/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:38:56 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 18:16:22 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec(t_exec **node, int r_fd, int w_fd, char *cmd)
{
	(*node)->cmd = cmd;
	(*node)->read_fd = r_fd;
	(*node)->write_fd = w_fd;
	(*node)->next = NULL;
}

int	count_mem(t_tokens *temp)
{
	int		count;

	count = 1;
	temp = temp->next;
	while (temp)
	{
		if (temp->type == T_WORD || temp->type == T_VARIABLE)
			count++;
		temp = temp->next;
	}
	return (count);
}

char	*expand_variable(char *data, t_shell *shell)
{
	t_env	*temp;

	temp = shell->env;
	if (is_single_quoted(data))
		return (remove_quotes_and_dollar(data, 0, shell));
	else
		data = remove_quotes_and_dollar(data, 1, shell);
	if (!ft_strncmp(data, "?", 1))
	{
		return (shell_ft_itoa(g_exit_status, shell));
	}
	while (temp)
	{
		if (!ft_strncmp(temp->data, data, ft_strlen(data)))
			return (make_expand(temp->data, data, shell));
		temp = temp->next;
	}
	data = shell_ft_strdup("", shell->allocs);
	return (data);
}

char	**set_argv(t_tokens *temp, t_shell *shell, int i)
{
	char	**argv;

	if (!temp)
		return (NULL);
	argv = oh_my_malloc(sizeof(char *) * (count_mem(temp) + 1), shell->allocs);
	if (!argv)
		return (NULL);
	argv[i] = shell_ft_strdup(temp->data, shell->allocs);
	temp = temp->next;
	i++;
	while (temp && (temp->type == T_WORD || temp->type == T_VARIABLE))
	{
		if (temp->type == T_VARIABLE)
			argv[i] = expand_variable(temp->data, shell);
		else
			argv[i] = shell_ft_strdup(temp->data, shell->allocs);
		if (!argv[i])
			return (NULL);
		i++;
		temp = temp->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_exec	*make_exec_node(t_tokens *temp, t_shell *shell, int r_fd, int w_fd)
{
	t_exec	*new;

	new = oh_my_malloc(sizeof(t_exec), shell->allocs);
	if (!new)
		return (NULL);
	init_exec(&new, r_fd, w_fd, temp->data);
	new->argv = set_argv(temp, shell, 0);
	return (new);
}
