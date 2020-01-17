/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:24:16 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/17 07:34:09 by cchudant         ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>

# define SEM_FORKS "/philo_forks"
# define SEM_STDOUT "/philo_stdout"
# define SEM_EAT_PREFIX "/philo_eat_"

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
	sem_t				*forks;
	sem_t				*stdout_semaphore;
	sem_t				**eating_semaphores;
	char				**eating_names;
}						t_global_state;

typedef struct			s_philoctx
{
	int					n;
	const t_philoargs	*args;
	t_global_state		*gbl;
	unsigned long		last_eat;
	pid_t				pid;
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

void					wait_children(t_philoctx *ctxs, int n_philo);
void					*monitor_one(void *ctx);

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
