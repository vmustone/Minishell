/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:44:34 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 18:13:03 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

char	*get_path(char *cmd, t_shell *shell)
{
	char	*path;
	char	**path_split;
	int		i;

	i = 0;
	path = get_env("PATH=", shell->env);
	if (!path)
		return (NULL);
	path_split = shell_ft_split(path, ':', shell);
	while (path_split[i])
	{
		path = shell_ft_strjoin(path_split[i], "/", shell);
		path = shell_ft_strjoin(path, cmd, shell);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

int	check_command(t_exec *exec, t_shell *shell)
{
	char	*path;

	if (access(exec->cmd, X_OK) == 0 || is_builtin(exec->cmd) == 1)
		return (0);
	path = get_path(exec->cmd, shell);
	if (!path)
	{
		write(2, "MINISHELL: ", 11);
		write(2, exec->cmd, ft_strlen(exec->cmd));
		write(2, ": command not found\n", 20);
		g_exit_status = 127;
		return (1);
	}
	exec->cmd = path;
	return (0);
}

int	dup_fds(t_exec *head, int org_write, int org_read)
{
	if (head->read_fd != 0)
	{
		if (dup2(head->read_fd, 0) == -1)
			return (write(2, "dup2 failed\n", 12));
	}
	else
	{
		if (dup2(org_read, 0) == -1)
			return (write(2, "dup2 failed\n", 12));
	}
	if (head->write_fd != 1)
	{
		if (dup2(head->write_fd, 1) == -1)
			return (write(2, "write dup2 failed\n", 12));
	}
	else
	{
		if (dup2(org_write, 1) == -1)
			return (write(2, "write dup2 failed\n", 12));
	}
	return (0);
}

void	executer(t_shell *shell, int org_write, int org_read)
{
	t_exec		*head;
	pid_t		current_pid;

	shell->pids = NULL;
	head = shell->exec;
	while (head)
	{
		if (check_command(head, shell) == 1)
			break ;
		signal(SIGINT, sig_handler_child);
		signal(SIGQUIT, sig_handler_child);
		current_pid = fork();
		if (current_pid == 0)
			child(head, shell, org_write, org_read);
		save_pid(current_pid, shell);
		head = head->next;
	}
	close_all_fds(shell, org_write, org_read);
	wait_pids(shell);
}
