/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 01:08:45 by aalemami          #+#    #+#             */
/*   Updated: 2025/09/22 01:08:45 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	fill_ptr_str(char **str, char *ptr, char **new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*str)[i] != '\n')
	{
		ptr[i] = (*str)[i];
		i++;
	}
	ptr[i++] = '\n';
	ptr[i] = '\0';
	while ((*str)[i])
		(*new_str)[j++] = (*str)[i++];
	(*new_str)[j] = '\0';
	if (length_finder(*new_str) == 0)
	{
		free(*new_str);
		*new_str = NULL;
	}
	free(*str);
	*str = *new_str;
}

char	*get_line_remake_str(char **str)
{
	char	*new_str;
	char	*ptr;

	if (*str == NULL)
		return (NULL);
	ptr = malloc((check_line(*str) + 2) * sizeof(char));
	new_str = malloc((length_finder(*str) - check_line(*str)) * sizeof(char));
	if (!ptr || !new_str)
	{
		free(ptr);
		free(new_str);
		free(*str);
		*str = NULL;
		return (NULL);
	}
	fill_ptr_str(str, ptr, &new_str);
	return (ptr);
}

char	*make_str_ptr(char **str, char **ptr, int *x)
{
	char	*new_ptr;
	int		i;
	int		j;

	(*ptr)[*x] = '\0';
	new_ptr = malloc((*x + length_finder(*str) + 1) * sizeof(char));
	if (!(new_ptr))
	{
		free(*str);
		*str = NULL;
		free(*ptr);
		*ptr = NULL;
		return (NULL);
	}
	i = 0;
	while (*str && (*str)[i])
	{
		new_ptr[i] = (*str)[i];
		i++;
	}
	j = 0;
	while ((*ptr)[j])
		new_ptr[i++] = (*ptr)[j++];
	new_ptr[i] = '\0';
	return (new_ptr);
}

char	*combine_str_ptr(char **str, int *x, int fd)
{
	char	*ptr;
	char	*temp;

	ptr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!ptr)
	{
		free(*str);
		*str = NULL;
		return (NULL);
	}
	*x = read(fd, ptr, BUFFER_SIZE);
	if (*x == -1 || ((*x) + length_finder(*str)) == 0)
	{
		free(ptr);
		free(*str);
		*str = NULL;
		return (NULL);
	}
	temp = make_str_ptr(str, &ptr, x);
	free(*str);
	*str = NULL;
	free(ptr);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*str;
	int			x;
	char		*ptr;

	if (BUFFER_SIZE < 1 || fd < 0 || fd >= 4096)
		return (NULL);
	if (check_line(str) != -1)
		return (get_line_remake_str(&str));
	ptr = combine_str_ptr(&str, &x, fd);
	if (!ptr)
		return (NULL);
	while (check_line(ptr) == -1)
	{
		str = ft_strcpy(&ptr);
		ptr = combine_str_ptr(&str, &x, fd);
		if (!ptr)
			return (NULL);
		if (x == 0)
			return (ptr);
	}
	str = ft_strcpy(&ptr);
	return (get_line_remake_str(&str));
}
