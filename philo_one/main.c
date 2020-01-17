/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:25:12 by cchudant          #+#    #+#             */
/*   Updated: 2020/01/16 17:14:52 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_pint(char *str)
{
	int res;

	res = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		res = res * 10 + *str - '0';
		str++;
	}
	return (res);
}

bool		handle_th_err(int err, char *str)
{
	if (err)
	{
		write(1, str, ft_strlen(str));
		exit(!err);
	}
	return (!err);
}

static bool	parse_args(t_philoargs *args, int ac, char **av)
{
	if (ac < 5)
		return (false);
	if ((args->n_philo = parse_pint(av[1])) < 1)
		return (false);
	if ((args->time_to_die = parse_pint(av[2])) < 0)
		return (false);
	if ((args->time_to_eat = parse_pint(av[3])) < 0)
		return (false);
	if ((args->time_to_sleep = parse_pint(av[4])) < 0)
		return (false);
	if (ac >= 6)
		return ((args->times_must_eat = parse_pint(av[5])) > 0);
	args->times_must_eat = 0;
	return (true);
}

int			main(int ac, char **av)
{
	t_philoargs		args;
	t_global_state	gbl;

	gbl = (t_global_state) { 0 };
	args = (t_philoargs) { .start = get_curr_time_ms() };
	if (!parse_args(&args, ac, av))
	{
		ft_putstr(2, "Usage: ");
		ft_putstr(2, av[0]);
		ft_putstr(2, " number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (!init_global_state(&args, &gbl) || !spawn_philos(&args, &gbl))
	{
		destroy_global_state(&args, &gbl);
		return (1);
	}
	destroy_global_state(&args, &gbl);
	return (0);
}
