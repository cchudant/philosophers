/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:50:50 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/08 08:09:22 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			ft_bufputulong(char *buf, int *index, unsigned long n)
{
	unsigned long b;

	b = 1;
	while (n / b >= 10)
		b *= 10;
	while (b > 0)
	{
		buf[(*index)++] = '0' + n / b % 10;
		b /= 10;
	}
}

void			ft_bufputstr(char *buf, int *index, char *str)
{
	int i;

	i = -1;
	while (str[++i])
		buf[(*index)++] = str[i];
}

unsigned long	get_curr_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}
