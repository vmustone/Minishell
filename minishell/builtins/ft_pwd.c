
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:07:09 by vmustone          #+#    #+#             */
/*   Updated: 2023/06/14 15:08:12 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	ft_pwd(void)
{
	char	current_dir[PATH_MAX];

	if (getcwd(current_dir, PATH_MAX))
	{
		printf("%s\n", current_dir);
		return (0);
	}
	else
		return (1);
}