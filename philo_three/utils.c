/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:25:35 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/08 08:05:46 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *s)
{
	int len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

ssize_t	ft_putstr(int fd, char *s)
{
	return (write(fd, s, ft_strlen(s)));
}

bool	ft_append(char **dst, char *s)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	s1l;

	s1l = *dst ? ft_strlen(*dst) : 0;
	if (!(tmp = malloc(sizeof(char) * (s1l + ft_strlen(s) + 1))))
		return (false);
	i = 0;
	while (i < s1l)
	{
		tmp[i] = (*dst)[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s))
	{
		tmp[i + j] = s[j];
		j++;
	}
	tmp[i + j + 1] = '\0';
	free(*dst);
	*dst = tmp;
	return (true);
}
