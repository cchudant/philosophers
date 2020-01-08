/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:50:50 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/08 08:51:05 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(const t_philoctx *ctx, t_philostatus s)
{
	char	buf[1024];
	int		index;

	index = 0;
	ft_bufputulong(buf, &index, get_curr_time_ms() - ctx->args->start);
	buf[index++] = ' ';
	ft_bufputulong(buf, &index, ctx->n + 1);
	if (s == EATING)
		ft_bufputstr(buf, &index, " is eating\n");
	else if (s == THINKING)
		ft_bufputstr(buf, &index, " is thinking\n");
	else if (s == SLEEPING)
		ft_bufputstr(buf, &index, " is sleeping\n");
	else if (s == TAKEN_FORK)
		ft_bufputstr(buf, &index, " has taken a fork\n");
	else if (s == DIED)
		ft_bufputstr(buf, &index, " died\n");
	write(1, buf, index);
}

void	*philo_entrypoint(void *v_ctx)
{
	t_philoctx	*ctx;
	int			i;

	ctx = v_ctx;
	i = -1;
	while (++i < ctx->args->times_must_eat || !ctx->args->times_must_eat)
	{
		print_status(ctx, THINKING);
		sem_wait(ctx->gbl->semaphore);
		print_status(ctx, TAKEN_FORK);
		sem_wait(ctx->gbl->semaphore);
		print_status(ctx, TAKEN_FORK);
		print_status(ctx, EATING);
		ctx->last_eat = get_curr_time_ms();
		usleep(ctx->args->time_to_eat * 1000);
		sem_post(ctx->gbl->semaphore);
		sem_post(ctx->gbl->semaphore);
		print_status(ctx, SLEEPING);
		usleep(ctx->args->time_to_sleep * 1000);
	}
	ctx->stopped = true;
	return (NULL);
}
