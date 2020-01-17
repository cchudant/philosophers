/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:24:16 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/16 10:52:32 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor_exit(t_philoctx *ctx)
{
	print_status(ctx, DIED);
	ctx->stopped = true;
	exit(0);
}

static void	*monitor_one(void *ctx_v)
{
	t_philoctx		*ctx;
	unsigned long	time;

	ctx = ctx_v;
	while (!ctx->stopped)
	{
		pthread_mutex_lock(&ctx->gbl->eating_mutexes[ctx->n]);
		time = get_curr_time_ms();
		if (time - ctx->last_eat >=
				(unsigned long)ctx->args->time_to_die)
			monitor_exit(ctx);
		pthread_mutex_unlock(&ctx->gbl->eating_mutexes[ctx->n]);
		usleep(8 * 1000);
	}
	return (NULL);
}

void		monitor(t_philoctx *ctxs, int n_philo)
{
	int i;

	i = -1;
	while (++i < n_philo)
		handle_th_err(pthread_create(&ctxs[i].monitor_thread, NULL,
				&monitor_one, &ctxs[i]),
				"Error: monitor pthread create failed!\n");
	i = -1;
	while (++i < n_philo)
		pthread_join(ctxs[i].monitor_thread, NULL);
	i = -1;
	while (++i < n_philo)
		pthread_join(ctxs[i].thread, NULL);
}
