/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:24:16 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/16 17:20:09 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum			e_philostatus
{
	EATING,
	THINKING,
	SLEEPING,
	TAKEN_FORK,
	DIED,
}						t_philostatus;

typedef struct			s_philoargs
{
	unsigned long		start;
	int					n_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_must_eat;
}						t_philoargs;

typedef struct			s_global_state
{
	bool				sim_stopped;
	pthread_mutex_t		stdout_mutex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*eating_mutexes;
}						t_global_state;

typedef struct			s_philoctx
{
	int					n;
	const t_philoargs	*args;
	t_global_state		*gbl;
	unsigned long		last_eat;
	bool				stopped;
	pthread_t			thread;
	pthread_t			monitor_thread;
}						t_philoctx;

void					*ft_calloc(size_t len);
size_t					ft_strlen(char *s);
ssize_t					ft_putstr(int fd, char *s);
bool					ft_append(char **dst, char *s);
void					ft_bufputulong(char *buf, int *index, unsigned long n);
void					ft_bufputstr(char *buf, int *index, char *str);
unsigned long			get_curr_time_ms(void);

bool					handle_th_err(int err, char *str);

void					monitor(t_philoctx *ctxs, int n_philo);

void					print_status(const t_philoctx *ctx, t_philostatus s);
bool					init_global_state(const t_philoargs *args,
							t_global_state *gbl);
void					destroy_global_state(const t_philoargs *args,
							t_global_state *gbl);
bool					spawn_philos(const t_philoargs *args,
							t_global_state *gbl);
void					*philo_entrypoint(void *ctx);

int						main(int ac, char **av);

#endif
