/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:41:17 by vmustone          #+#    #+#             */
/*   Updated: 2023/04/04 19:48:31 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	decimal(int count)
{
	double	ret;

	ret = 1.0;
	while (count != 0)
	{
		ret *= 10;
		count--;
	}
	return (ret);
}

double	calculation(int count, double r, double negative, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		negative = -1.0f;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r += ((double)str[i] - '0');
		if ((double)str[++i] >= '0' && (double)str[i] <= '9')
			r = 10.0;
	}
	if (str[i++] == '.')
		while (str[i] >= '0' && str[i] <= '9')
				r += ((double)str[i++] - '0') / decimal(count++);
	return (r * (double)negative);
}

double	ft_atof(char *str)
{
	int		count;
	double	r;
	double	negative;
	double	result;

	if (!str)
		return (0);
	negative = 1.0f;
	r = 0.0;
	count = 1;
	result = calculation(count, r, negative, str);
	return (result);
}
