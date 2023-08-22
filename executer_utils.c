/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:39:00 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/19 14:18:36 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->data, ft_strlen(var)) == 0)
			return (tmp->data);
		tmp = tmp->next;
	}
	return (NULL);
}

int	execute_command(t_exec *exec, t_shell *shell)
{
	if (is_builtin(exec->cmd) == 1)
	{
		return (builtin(exec, shell));
	}
	else
	{
		return (execve(exec->cmd, exec->argv, shell->org_env));
	}
	return (0);
}

void	save_pid(pid_t pid, t_shell *shell)
{
	t_pid	*new;
	t_pid	*tmp;

	new = oh_my_malloc(sizeof(t_pid), shell->allocs);
	new->pid = pid;
	new->next = NULL;
	if (!shell->pids)
		shell->pids = new;
	else
	{
		tmp = shell->pids;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	save_fds(int *org_write, int *org_read)
{
	*org_write = dup(1);
	*org_read = dup(0);
	if (*org_write == -1 || *org_read == -1)
	{
		ft_error("dup failed");
		return (-1);
	}
	return (0);
}

void	close_all_fds(t_shell *shell, int org_write, int org_read)
{
	t_exec	*tmp;

	if (shell && shell->exec)
		tmp = shell->exec;
	else
		tmp = NULL;
	while (shell && tmp)
	{
		if (tmp->read_fd != 0)
			close(tmp->read_fd);
		if (tmp->write_fd != 1)
			close(tmp->write_fd);
		tmp = tmp->next;
	}
	if (org_write != 1 && org_read != 0)
	{
		close(org_write);
		close(org_read);
	}
}
