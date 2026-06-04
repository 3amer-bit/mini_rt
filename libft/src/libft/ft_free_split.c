/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 18:04:52 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/22 14:56:07 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **str)
{
	char	**tmp;

	if (!str)
		return ;
	tmp = str;
	while (*str)
		free(*str++);
	free(tmp);
}
