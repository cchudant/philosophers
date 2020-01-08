/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:24:16 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/08 13:50:59 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*monitor_one(void *v_ctx)
{
	t_philoctx *ctx;

	ctx = v_ctx;
	while (1)
	{
		if (get_curr_time_ms() - ctx->last_eat >=
				(unsigned long)ctx->args->time_to_die)
		{
			print_status(ctx, DIED);
			exit(0);
		}
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
