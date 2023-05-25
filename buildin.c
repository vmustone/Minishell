/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:25:59 by vmustone          #+#    #+#             */
/*   Updated: 2023/05/25 19:19:37 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	ft_echo(char **argv)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1] && argv[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (newline == 1)
		printf("\n");
	return (0);
}

char	*get_current_dir(void)
{
	char	*buffer;
	char	*dir;

	buffer = malloc(sizeof(char) * PATH_MAX);
	if (!buffer)
		return (NULL);
	dir = getcwd(buffer, PATH_MAX);
	free(buffer);
	return (dir);
}

int	ft_cd(const char *dir_path)
{
	const char	*dir_home;
	
	if (dir_path == NULL || dir_path[0] == '\0')
	{
		dir_home = getenv("HOME");
		if (dir_home == NULL)
			return (1);
		if (chdir(dir_home) != 0)
			return (1);
	}
	else
	{
		if (chdir(dir_path) != 0)
			return (1);
	}
	return (0);
}


int main()
{
	char	*input;

	while (1)
	{
		input = readline("minishell ");
		//ft_cd(input);
		ft_echo(&input);
		//printf("%s\n", get_current_dir());
	}
	return (0);
}