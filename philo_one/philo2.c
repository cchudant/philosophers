/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:50:50 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/08 08:27:35 by cchudant         ###   ########.fr       */
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

void	philo_take_forks(t_philoctx *ctx)
{
	int first;
	int second;

	first = ctx->n % 2 == 0 ? ctx->n : (ctx->n + 1) % ctx->args->n_philo;
	second = ctx->n % 2 != 0 ? ctx->n : (ctx->n + 1) % ctx->args->n_philo;
	handle_th_err(pthread_mutex_lock(&ctx->gbl->forks[first]),
		"Error while locking the mutex!\n");
	print_status(ctx, TAKEN_FORK);
	handle_th_err(pthread_mutex_lock(&ctx->gbl->forks[second]),
		"Error while locking the mutex!\n");
	print_status(ctx, TAKEN_FORK);
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
		philo_take_forks(ctx);
		print_status(ctx, EATING);
		ctx->last_eat = get_curr_time_ms();
		usleep(ctx->args->time_to_eat * 1000);
		handle_th_err(pthread_mutex_unlock(&ctx->gbl->forks[ctx->n]),
			"Error while unlocking the mutex!\n");
		handle_th_err(pthread_mutex_unlock(
			&ctx->gbl->forks[(ctx->n + 1) % ctx->args->n_philo]),
			"Error while unlocking the mutex!\n");
		print_status(ctx, SLEEPING);
		usleep(ctx->args->time_to_sleep * 1000);
	}
	ctx->stopped = true;
	return (NULL);
}
