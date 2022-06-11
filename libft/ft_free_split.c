/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 22:01:18 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/11 19:22:33 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(void ***split)
{
	void	**sp;

	sp = *split;
	while (*sp)
		ft_memfree((void *) sp++);
	ft_memfree((void *) split);
}
