/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:58:17 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:15:45 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int		check_filename(char *filename)
{
	while (*filename && *filename != '.')
		filename++;
	if (ft_strcmp(filename, ".cub"))
		return (0);
	return (1);
}

char	**parsing(char *filename)
{
	int		fd;
	char	*line;
	int		i;
	char	**data;
	int		n;

	if ((fd = open(filename, O_RDONLY)) < 0 || !check_filename(filename))
		return (NULL);
	i = 0;
	while (read(fd, &n, 1))
		if (n == '\n')
			i++;
	close(fd);
	if (!(data = (char**)malloc(sizeof(char*) * (i + 2))))
		return (NULL);
	fd = open(filename, O_RDONLY);
	n = 0;
	while (n < i)
	{
		get_next_line(fd, &line);
		data[n++] = line;
	}
	data[n] = NULL;
	close(fd);
	return (data);
}
