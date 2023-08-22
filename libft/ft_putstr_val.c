/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:57:28 by vmustone          #+#    #+#             */
/*   Updated: 2022/12/12 12:08:08 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_val(char *s)
{
	int	ret;

	ret = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (*s)
	{
		ft_putchar_val(*s);
		s++;
		ret++;
	}
	return (ret);
}
