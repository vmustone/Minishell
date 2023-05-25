
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:20:25 by vmustone          #+#    #+#             */
/*   Updated: 2023/05/25 16:20:45 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_cd(char *dir_path)
{
	char	*dir_home;

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