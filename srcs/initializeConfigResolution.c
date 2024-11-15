/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 09:56:25 by admadene          #+#    #+#             */
/*   Updated: 2020/02/22 09:56:26 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>


static char	*skipWhitespaces(char *str)
{
	while (*str && ft_isspace(*str))
		++str;
	return (str);
}

void	freeTab(char **tab)
{
	int i = 0;
	while (tab[i]) {
		free(tab[i]);
		++i;
	}
	free(tab);
}

int		initializeConfigResolution(t_cub *s)
{
	char	**tokenizeLine = NULL;
	for (int i = 0; s->_config._fileDuplicate[i]; ++i) {
		if (*skipWhitespaces(s->_config._fileDuplicate[i]) == 'R') {
			tokenizeLine = ft_split_charset(s->_config._fileDuplicate[i], " \t\r");
			
			if (tokenizeLine[1] == NULL)
				return (0);
			s->_config._resolutionWidth = ft_atoi(tokenizeLine[1]);

			if (tokenizeLine[2] == NULL)
				return (0);
			s->_config._resolutionHeight = ft_atoi(tokenizeLine[2]);
		
			if (tokenizeLine[3] != NULL)
				return (0);
			
			if (s->_config._resolutionWidth <= 0 || s->_config._resolutionHeight <= 0)
				return (0);	
			if (s->_config._resolutionWidth > RESOLUTION_WIDTH_MAX || s->_config._resolutionHeight > RESOLUTION_HEIGHT_MAX)
			{
				s->_config._resolutionWidth = RESOLUTION_WIDTH_MAX;
				s->_config._resolutionHeight = RESOLUTION_HEIGHT_MAX;
			}
			suppr_line(s->_config._fileDuplicate, i);
			freeTab(tokenizeLine);
			return (1);			
		}
	}
	return (0);
}
