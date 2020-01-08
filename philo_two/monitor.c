/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:24:16 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/08 08:11:57 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor_exit(t_philoctx *ctx)
{
	pthread_detach(ctx->thread);
	print_status(ctx, DIED);
	ctx->stopped = true;
	exit(0);
}

void		monitor(t_philoctx *ctxs, int n_philo)
{
	unsigned long	time;
	int				i;
	bool			all_done;

	all_done = false;
	while (!all_done)
	{
		all_done = true;
		time = get_curr_time_ms();
		i = -1;
		while (++i < n_philo)
		{
			if (ctxs[i].stopped)
				continue;
			all_done = false;
			if (time - ctxs[i].last_eat >=
					(unsigned long)ctxs[i].args->time_to_die)
				monitor_exit(&ctxs[i]);
		}
		usleep(8 * 1000);
	}
}
