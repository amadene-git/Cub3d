/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:20:06 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:12:52 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char*)s;
	while (n--)
		*str++ = 0;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	str = malloc(nmemb * size);
	ft_bzero(str, nmemb * size);
	return (str);
}
