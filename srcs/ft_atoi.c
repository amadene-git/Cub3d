/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:52:29 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:12:24 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int			ft_atoi(const char *str)
{
	int i;
	int res;
	int sign;

	i = 0;
	res = 0;
	while (ft_isspace(*(str + i)))
		i++;
	sign = (*(str + i) == '-') ? -1 : 1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (ft_isdigit(*(str + i)))
	{
		res = (res * 10) + ((*(str + i) - '0') * sign);
		i++;
	}
	return (res);
}
