/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:50:50 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/20 15:54:25 by cchudant         ###   ########.fr       */
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
	sem_wait(ctx->gbl->stdout_semaphore);
	write(1, buf, index);
	if (s != DIED)
		sem_post(ctx->gbl->stdout_semaphore);
}

void	philo_take_forks_and_eat(t_philoctx *ctx)
{
	sem_wait(ctx->gbl->forks);
	print_status(ctx, TAKEN_FORK);
	sem_wait(ctx->gbl->forks);
	print_status(ctx, TAKEN_FORK);
	print_status(ctx, EATING);
	sem_wait(ctx->gbl->eating_semaphores[ctx->n]);
	ctx->last_eat = get_curr_time_ms();
	usleep(ctx->args->time_to_eat * 1000);
	sem_post(ctx->gbl->forks);
	sem_post(ctx->gbl->forks);
	sem_post(ctx->gbl->eating_semaphores[ctx->n]);
}

void	*philo_entrypoint(void *v_ctx)
{
	pthread_t	monitor;
	t_philoctx	*ctx;
	int			i;

	ctx = v_ctx;
	i = 0;
	usleep(1);
	handle_th_err(pthread_create(&monitor, NULL, &monitor_one, ctx),
			"Error: pthread create failed!\n");
	while (1)
	{
		print_status(ctx, THINKING);
		philo_take_forks_and_eat(ctx);
		if (++i >= ctx->args->times_must_eat && ctx->args->times_must_eat)
			break ;
		print_status(ctx, SLEEPING);
		usleep(ctx->args->time_to_sleep * 1000);
	}
	exit(0);
	return (NULL);
}
