/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_floor_ceiling_init.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admadene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:39:23 by admadene          #+#    #+#             */
/*   Updated: 2020/02/06 17:16:24 by admadene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static int isStrDigit(const char *str) {
	if (str == NULL || *str == '\0')
		return (0);
	while (*str) {
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

static int convertColor(char *destColorPtr, char *strToConvert) {
	int color = 0;

	color = ft_atoi(strToConvert);
	if (color > 255)
		return (0);
	destColorPtr[0] = color;
	return (1);
}

static int	initializeBackgroundColorByTagName(char **fileDuplicate, const char *tag, int *color) {
	char	**tokenizeLine = NULL;
	char	**tokenizeColor = NULL;
	char	*colorPtr = (char*)color;

	for (int i = 0; fileDuplicate[i]; ++i) {
		if (*skipWhitespaces(fileDuplicate[i]) == tag[0]) {
			tokenizeLine = ft_split_charset(fileDuplicate[i], WHITESPACE_CHARSET);
			if (ft_strcmp(tokenizeLine[0], tag) != 0
			  || tokenizeLine[0] == NULL
			  || tokenizeLine[1] == NULL
			  || tokenizeLine[2] != NULL)
				return (0);

			tokenizeColor = ft_split_charset(tokenizeLine[1], ",");
			if (tokenizeColor[0] == NULL || !isStrDigit(tokenizeColor[0])
			  || tokenizeColor[1] == NULL || !isStrDigit(tokenizeColor[1])
			  || tokenizeColor[2] == NULL || !isStrDigit(tokenizeColor[2])
			  || tokenizeColor[3] != NULL)
				return (0);

			if (!convertColor(&colorPtr[0], tokenizeColor[2])
			  || !convertColor(&colorPtr[1], tokenizeColor[1])
			  || !convertColor(&colorPtr[2], tokenizeColor[0]))
				return (0);

			freeTab(tokenizeLine);
			freeTab(tokenizeColor);
			return (1);
		}
	}
	return (0);
}

int	initializeBackgroundColors(t_fileConfig *config) {
	if (!initializeBackgroundColorByTagName(config->_fileDuplicate, "C", &config->_backgroundColor._ceiling)
	  || !initializeBackgroundColorByTagName(config->_fileDuplicate, "F", &config->_backgroundColor._floor))
		return (0);
	return (1);
}

