/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:50:50 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/08 08:16:40 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_global_state(const t_philoargs *args, t_global_state *gbl)
{
	int i;

	if (!(gbl->forks = malloc(sizeof(pthread_mutex_t) * args->n_philo)))
		return (false);
	i = 0;
	while (i < args->n_philo)
		handle_th_err(pthread_mutex_init(&gbl->forks[i++], NULL),
				"Error: mutex initialization failed!\n");
	return (true);
}

void	destroy_global_state(const t_philoargs *args, t_global_state *gbl)
{
	int i;

	i = 0;
	while (i < args->n_philo)
		pthread_mutex_destroy(&gbl->forks[i++]);
	free(gbl->forks);
}

bool	spawn_philos(const t_philoargs *args, t_global_state *gbl)
{
	t_philoctx	*ctxs;
	int			i;

	if (!(ctxs = malloc(sizeof(t_philoctx) * args->n_philo)))
		return (false);
	i = 0;
	while (i < args->n_philo)
	{
		ctxs[i] = (t_philoctx) { .n = i, .args = args, .gbl = gbl,
			.last_eat = args->start };
		handle_th_err(pthread_create(&ctxs[i].thread, NULL,
				&philo_entrypoint, &ctxs[i]),
				"Error: pthread create failed!\n");
		i++;
	}
	i = 0;
	monitor(ctxs, args->n_philo);
	free(ctxs);
	return (true);
}
