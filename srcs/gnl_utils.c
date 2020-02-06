/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:30:10 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:15:11 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

char	*ft_chr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char*)s);
		s++;
	}
	if (!*s && !c)
		return ((char*)s);
	return (NULL);
}

size_t	ft_strlen(char const *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char const *s)
{
	char	*str;
	char	*strcpy;

	str = (char*)malloc(sizeof(char) * (ft_strlen((char*)s) + 1));
	if (str == NULL)
		return (NULL);
	strcpy = str;
	while (*s)
		*strcpy++ = *s++;
	*strcpy = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len;
	char	*cpy;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	cpy = s1;
	len = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	free(cpy);
	return (str - len);
}

char	*ft_sub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (ft_strdup(""));
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (start >= ft_strlen((char*)s))
	{
		*str = '\0';
		return (str);
	}
	s += start;
	while (i++ < len && *s)
		*str++ = *s++;
	*str = '\0';
	return (str - i + 1);
}
