/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:17:21 by lbroms            #+#    #+#             */
/*   Updated: 2023/08/11 18:51:02 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*oh_my_malloc(size_t size, t_allocations *allocs)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		ft_error("malloc failed");
		return (NULL);
	}
	allocs->allocations[allocs->count] = ret;
	allocs->count += 1;
	return (ret);
}

void	oh_my_free(t_allocations *allocs)
{
	int	i;

	i = 0;
	while (i < allocs->count)
	{
		free(allocs->allocations[i]);
		allocs->allocations[i] = NULL;
		i++;
	}
	free(allocs);
}
