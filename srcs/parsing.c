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
	int i;

	i = 0;
	while (filename[i])
		i++;
	if (i >= 4 && ft_strcmp(filename + i - 4, ".cub"))
		return (0);
	return (1);
}

int		check_file(char *filename)
{
	int fd;

	if ((fd = open(((const char*)(filename)), O_RDONLY)) == -1)
		return (0);
	close(fd);
	return (1);
}

void	suppr_line(char **tab, int i)
{
	free(tab[i]);
	while (tab[i])
	{
		tab[i] = tab[i + 1];
		i++;
	}
}

int		is_end_space(char *str)
{
	while (*str)
		if (*str++ != ' ')
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
	while (read(fd, (char*)&n, 1))
		if ((char)n == '\n')
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
