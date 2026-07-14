/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 01:08:42 by aalemami          #+#    #+#             */
/*   Updated: 2025/09/22 01:08:42 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_line(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	length_finder(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char **src)
{
	int		i;
	char	*temp;

	if (length_finder(*src) == 0)
		return (NULL);
	temp = malloc((length_finder(*src) + 1) * sizeof(char));
	if (!temp)
	{
		free(*src);
		*src = NULL;
		return (NULL);
	}
	i = 0;
	while ((*src)[i])
	{
		temp[i] = (*src)[i];
		i++;
	}
	temp[i] = '\0';
	free(*src);
	*src = NULL;
	return (temp);
}
