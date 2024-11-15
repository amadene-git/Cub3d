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

#include <cub.h>

int		checkFilenameExtension(const char *filename, const char *extension)
{
	char *str = ft_strrchr(filename, '.');
	if (ft_strcmp(str, extension))
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

char	**fileDuplicate(const char *filename)
{
	if (!checkFilenameExtension(filename, ".cub"))
		return (NULL);

	return (ft_getFile(filename));
}
