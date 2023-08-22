/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:09:14 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 17:19:21 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(t_exec *exec, t_shell *shell)
{
	if (ft_strcmp(exec->cmd, "echo") == 0)
		return (ft_echo(exec->argv));
	if (ft_strcmp(exec->cmd, "cd") == 0)
		return (ft_cd(exec->argv, shell->env));
	if (ft_strcmp(exec->cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(exec->cmd, "export") == 0)
		return (ft_export(set_expansion(exec, shell), shell->env));
	if (ft_strcmp(exec->cmd, "unset") == 0)
		return (ft_unset(set_expansion(exec, shell), shell->env));
	if (ft_strcmp(exec->cmd, "env") == 0)
		return (ft_env(shell->env));
	if (ft_strcmp(exec->cmd, "exit") == 0)
		ft_exit(exec->argv, shell->allocs);
	return (0);
}

void	wait_pids(t_shell *shell)
{
	t_pid	*tmp;
	int		status;

	tmp = shell->pids;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		tmp = tmp->next;
	}
}
