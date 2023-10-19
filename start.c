/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcos- <amarcos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:40:27 by amarcos-          #+#    #+#             */
/*   Updated: 2023/10/18 09:42:09 by amarcos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	startforks(pthread_mutex_t *forks, int n_philosophers)
{
	int	i;

	i = 0;
	while (i < n_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	startargs(t_philosophers *philosophers, char **argv)
{
	philosophers->timetodie = ft_atoi(argv[2]);
	philosophers->timetoeat = ft_atoi(argv[3]);
	philosophers->timetosleep = ft_atoi(argv[4]);
	philosophers->n_philos = ft_atoi(argv[1]);
	if (argv[5])
		philosophers->n_timestoeat = ft_atoi(argv[5]);
	else
		philosophers->n_timestoeat = -1;
}

void	startphilosohpers(t_philosophers *philosophers, t_program *program,
		pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philosophers[i].id = i + 1;
		philosophers[i].eating = 0;
		philosophers[i].meals = 0;
		startargs(&philosophers[i], argv);
		philosophers[i].startime = getcurrenttime();
		philosophers[i].lastmeal = getcurrenttime();
		philosophers[i].writelock = &program->writelock;
		philosophers[i].deadlock = &program->deadlock;
		philosophers[i].meallock = &program->meallock;
		philosophers[i].dead = &program->deadflag;
		philosophers[i].lfork = &forks[i];
		if (i == 0)
			philosophers[i].rfork = &forks[philosophers[i].n_philos - 1];
		else
			philosophers[i].rfork = &forks[i - 1];
		i++;
	}
}

void	start(t_program *program, t_philosophers *philosophers)
{
	program->deadflag = 0;
	program->philos = philosophers;
	pthread_mutex_init(&program->writelock, NULL);
	pthread_mutex_init(&program->deadlock, NULL);
	pthread_mutex_init(&program->meallock, NULL);
}
