/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:09:08 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/21 17:57:59 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_exit_status(int status)
{
	g_exit_status = status;
	return (status);
}

int	minishell(char *input, t_shell *shell, int org_write, int org_read)
{
	save_fds(&org_write, &org_read);
	shell->tokens = lexer(input, shell);
	if (!shell->tokens || check_for_arrangement_errors(shell->tokens))
	{
		close_all_fds(NULL, org_write, org_read);
		return (set_exit_status(258));
	}
	shell->exec = parser(shell);
	if (!shell->exec || g_exit_status == 420)
	{
		close_all_fds(NULL, org_write, org_read);
		return (set_exit_status(258));
	}
	if (shell->exec->next == NULL && is_builtin(shell->exec->cmd)
		&& shell->exec->write_fd == 1 && shell->exec->read_fd == 0)
	{
		g_exit_status = builtin(shell->exec, shell);
		close_all_fds(shell, org_write, org_read);
		return (0);
	}
	else
		executer(shell, org_write, org_read);
	unlink_heredocs(shell);
	return (0);
}

void	the_loop(t_shell *shell, struct termios ter, int first_time)
{
	char	*input;

	while (1)
	{
		if (!first_time)
			shell->allocs = init_allocs();
		shell->here_docs = init_here_docs(shell);
		signal_start();
		close_echo(&ter);
		input = readline("MINISHELL$ ");
		reset_echo(&ter);
		if (!input)
			handle_ctrl_d();
		if (input && *input)
		{
			add_history(input);
			minishell(input, shell, 1, 0);
		}
		oh_my_free(shell->allocs);
		free(input);
		first_time = 0;
	}
}

void	init_shell(t_shell *shell, char **ev, int ac)
{
	if (ac != 1)
		exit (0);
	shell->allocs = init_allocs();
	shell->org_env = ev;
}

int	main(int ac, char **av, char **ev)
{
	t_shell			shell;
	struct termios	ter;

	(void)av;
	init_shell(&shell, ev, ac);
	shell.env = env_init(shell.org_env, shell.allocs);
	tcgetattr(STDIN_FILENO, &ter);
	the_loop(&shell, ter, 1);
	return (0);
}
