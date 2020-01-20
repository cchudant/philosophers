/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:24:16 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/20 16:07:13 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor_exit(t_philoctx *ctx)
{
	print_status(ctx, DIED);
	exit(0);
}

void		*monitor_one(void *ctx_v)
{
	t_philoctx		*ctx;
	unsigned long	time;

	ctx = ctx_v;
	while (1)
	{
		sem_wait(ctx->gbl->eating_semaphores[ctx->n]);
		time = get_curr_time_ms();
		if (time - ctx->last_eat >
				(unsigned long)ctx->args->time_to_die)
			monitor_exit(ctx);
		sem_post(ctx->gbl->eating_semaphores[ctx->n]);
		usleep(8 * 1000);
	}
	return (NULL);
}

void		wait_children(t_philoctx *ctxs, int n_philo)
{
	int status;
	int i;

	(void)ctxs;
	(void)n_philo;
	while (1)
	{
		status = 0;
		if (waitpid(-1, &status, 0) < 0 || WIFEXITED(status))
		{
			i = -1;
			while (++i < n_philo)
				kill(ctxs[i].pid, SIGINT);
			exit(WEXITSTATUS(status));
		}
	}
}
