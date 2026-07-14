/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:05:30 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/22 15:57:45 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(const char **arr)
{
	int	i;

	i = 0;
	while (*arr++)
		i++;
	return (i);
}

char	**ft_strdup_2d(const char **arr)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (get_size(arr) + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			ft_free_split(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}
