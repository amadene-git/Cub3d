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

int		initializeConfigResolution(t_fileConfig *config)
{
	char	**tokenizeLine = NULL;
	for (int i = 0; config->_fileDuplicate[i]; ++i) {
		if (*skipWhitespaces(config->_fileDuplicate[i]) == 'R') {
			tokenizeLine = ft_split_charset(config->_fileDuplicate[i], WHITESPACE_CHARSET);
			
			if (ft_strcmp(tokenizeLine[0], "R") != 0
			  || tokenizeLine[1] == NULL
			  || tokenizeLine[2] == NULL
			  || tokenizeLine[3] != NULL)
				return (0);
			
			config->_resolutionWidth = ft_atoi(tokenizeLine[1]);
			config->_resolutionHeight = ft_atoi(tokenizeLine[2]);
			if (config->_resolutionWidth <= 0 || config->_resolutionHeight <= 0)
				return (0);	
			if (config->_resolutionWidth > RESOLUTION_WIDTH_MAX || config->_resolutionHeight > RESOLUTION_HEIGHT_MAX)
			{
				config->_resolutionWidth = RESOLUTION_WIDTH_MAX;
				config->_resolutionHeight = RESOLUTION_HEIGHT_MAX;
			}
			freeTab(tokenizeLine);
			return (1);			
		}
	}
	return (0);
}
