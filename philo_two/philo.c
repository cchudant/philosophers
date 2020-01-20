/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:50:50 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/20 15:53:48 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	wrap_sem_open(sem_t **dst, char *name, int init)
{
	sem_unlink(name);
	*dst = sem_open(name, O_CREAT, 0666, init);
	if (!*dst || *dst == SEM_FAILED)
	{
		ft_putstr(1, "Error: cannot create semaphore!\n");
		return (false);
	}
	return (true);
}

bool	create_sem_name(char **dst)
{
	static char	next_name[] = { 'a', 'a', 'a', 'a', '\0' };
	int			i;
	int			index;

	if (!(*dst = ft_calloc(sizeof(char) * (ft_strlen(SEM_EAT_PREFIX) + 4 + 1))))
		return (false);
	i = 0;
	while (i < 4 && next_name[i] == 'z')
		i++;
	if (i >= 4)
		return (false);
	index = 0;
	ft_bufputstr(*dst, &index, SEM_EAT_PREFIX);
	ft_bufputstr(*dst, &index, next_name);
	(*dst)[index] = '\0';
	next_name[i]++;
	return (true);
}

bool	init_global_state(const t_philoargs *args, t_global_state *gbl)
{
	int i;

	if (!wrap_sem_open(&gbl->forks, SEM_FORKS, args->n_philo) ||
		!wrap_sem_open(&gbl->stdout_semaphore, SEM_STDOUT, 1))
		return (false);
	if (!(gbl->eating_names = ft_calloc(sizeof(char *) * args->n_philo)) ||
		!(gbl->eating_semaphores = ft_calloc(sizeof(sem_t *) * args->n_philo)))
		return (false);
	i = -1;
	while (++i < args->n_philo)
		if (!create_sem_name(&gbl->eating_names[i]))
			return (false);
	i = -1;
	while (++i < args->n_philo)
		if (!wrap_sem_open(&gbl->eating_semaphores[i], gbl->eating_names[i], 1))
			return (false);
	return (true);
}

void	destroy_global_state(const t_philoargs *args, t_global_state *gbl)
{
	int i;

	(void)args;
	sem_close(gbl->forks);
	sem_close(gbl->stdout_semaphore);
	i = -1;
	while (++i < args->n_philo)
		free(gbl->eating_names[i]);
	i = -1;
	while (++i < args->n_philo)
		sem_close(gbl->eating_semaphores[i]);
	free(gbl->eating_names);
	free(gbl->eating_semaphores);
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
