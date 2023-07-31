/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:58:59 by vmustone          #+#    #+#             */
/*   Updated: 2023/05/11 21:36:25 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long int	ft_atoll(const char *str)
{
	int				sign;
	long long int	res;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
		if (res < 0)
			return (2147483648);
	}
	return (res * sign);
}
