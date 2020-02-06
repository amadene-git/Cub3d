/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_suppr_char_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:22:38 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:14:54 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

char	*suppr_char_string(char *str, int n)
{
	char	*ret;
	int		i;
	int		j;

	if (!(ret = (char*)ft_calloc(sizeof(char), (ft_strlen(str)))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i != n)
			ret[j++] = str[i++];
		else if (str[i])
			i++;
	}
	free(str);
	return (ret);
}
