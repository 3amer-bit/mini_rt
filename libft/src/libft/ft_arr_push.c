/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 22:05:37 by aalemami          #+#    #+#             */
/*   Updated: 2026/05/02 22:05:49 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}
static char	**strdup_2d(char **new_arr, char **arr, char *new_str)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			ft_free_split(new_arr);
			ft_free_split(arr);
			free(new_str);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = new_str;
	new_arr[++i] = NULL;
	ft_free_split(arr);
	return (new_arr);
}

char	**ft_arr_push(char **arr, char *str)
{
	char	**new_arr;
	char	*new_str;

	if (!str)
		return (arr);
	new_str = ft_strdup(str);
	if (!new_str)
	{
		ft_free_split(arr);
		return (NULL);
	}
	new_arr = malloc(sizeof(char*) * (get_size(arr) + 2));
	if (!new_arr)
	{
		free(new_str);
		ft_free_split(arr);
		return (NULL);
	}
	return (strdup_2d(new_arr, arr, new_str));
}
