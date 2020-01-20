/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:50:50 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/20 15:52:32 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_global_state(const t_philoargs *args, t_global_state *gbl)
{
	int i;

	if (!(gbl->forks = ft_calloc(sizeof(pthread_mutex_t) * args->n_philo)))
		return (false);
	if (!(gbl->eating_mutexes = ft_calloc(sizeof(pthread_mutex_t)
			* args->n_philo)))
		return (false);
	handle_th_err(pthread_mutex_init(&gbl->stdout_mutex, NULL),
			"Error: stdout mutex initialization failed!\n");
	i = -1;
	while (++i < args->n_philo)
		handle_th_err(pthread_mutex_init(&gbl->forks[i], NULL),
				"Error: mutex initialization failed!\n");
	i = -1;
	while (++i < args->n_philo)
		handle_th_err(pthread_mutex_init(&gbl->eating_mutexes[i], NULL),
				"Error: monitor mutex initialization failed!\n");
	return (true);
}

void	destroy_global_state(const t_philoargs *args, t_global_state *gbl)
{
	int i;

	i = 0;
	while (i < args->n_philo)
		pthread_mutex_destroy(&gbl->forks[i++]);
	i = 0;
	while (i < args->n_philo)
		pthread_mutex_destroy(&gbl->eating_mutexes[i++]);
	pthread_mutex_destroy(&gbl->stdout_mutex);
	free(gbl->forks);
	free(gbl->eating_mutexes);
}

bool	spawn_philos(const t_philoargs *args, t_global_state *gbl)
{
	t_philoctx	*ctxs;
	int			i;

	if (!(ctxs = ft_calloc(sizeof(t_philoctx) * args->n_philo)))
		return (false);
	i = -1;
	while (++i < args->n_philo)
	{
		ctxs[i] = (t_philoctx) { .n = i, .args = args, .gbl = gbl,
			.last_eat = args->start };
		handle_th_err(pthread_create(&ctxs[i].thread, NULL,
				&philo_entrypoint, &ctxs[i]),
				"Error: pthread create failed!\n");
		usleep(10);
	}
	monitor(ctxs, args->n_philo);
	free(ctxs);
	return (true);
}
