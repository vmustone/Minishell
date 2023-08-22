/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:16:09 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/20 20:09:46 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_heredocs(t_shell *shell)
{
	int	i;

	i = 0;
	while (i <= shell->here_docs->count)
	{
		unlink(shell->here_docs->doc_name[i]);
		i++;
	}
	shell->here_docs->count = 0;
}

char	*here_doc_helper(char *input, int fd)
{
	ft_putstr_fd(input, fd);
	write(fd, "\n", 1);
	free(input);
	input = readline(">");
	return (input);
}

int	choose_right_doc(t_shell *shell, int flag)
{
	int	fd;

	if (!flag)
	{
		fd = open(shell->here_docs->doc_name[shell->here_docs->count],
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
		return (fd);
	}
	if (flag == 1)
	{
		fd = open(shell->here_docs->doc_name[shell->here_docs->count],
				O_RDONLY);
		shell->here_docs->count++;
		return (fd);
	}
	return (0);
}

int	here_doc(char *delimeter, t_shell *shell)
{
	struct termios	t;
	char			*input;
	int				fd;

	tcgetattr(0, &t);
	signal(SIGINT, sigint_heredoc);
	close_echo(&t);
	fd = choose_right_doc(shell, 0);
	input = readline(">");
	if (input == NULL)
	{
		close(fd);
		fd = choose_right_doc(shell, 1);
		return (fd);
	}
	while (ft_strcmp(input, delimeter) != 0)
		input = here_doc_helper(input, fd);
	reset_echo(&t);
	signal(SIGINT, SIG_IGN);
	close(fd);
	fd = choose_right_doc(shell, 1);
	free(input);
	return (fd);
}
