/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:39:59 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/03 20:47:03 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const void	*start_dest = dest;

	if (dest > src)
		while (n--)
			*((char *) dest + n) = *((char *) src + n);
	else if (dest < src)
		while (n--)
			*(char *) dest++ = *(char *) src++;
	return ((void *) start_dest);
}
