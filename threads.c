/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcos- <amarcos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:28:37 by amarcos-          #+#    #+#             */
/*   Updated: 2023/10/19 08:42:25 by amarcos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	deadflagchange(t_philosophers *philosophers)
{
	pthread_mutex_lock(philosophers->deadlock);
	if (*philosophers->dead == 1)
		return (pthread_mutex_unlock(philosophers->deadlock), 1);
	pthread_mutex_unlock(philosophers->deadlock);
	return (0);
}

void	*philoroutine(void *pointer)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)pointer;
	if (philosophers->id % 2 == 0)
		customusleep(1);
	while (!deadflagchange(philosophers))
	{
		eat(philosophers);
		dream(philosophers);
		think(philosophers);
	}
	return (pointer);
}

int	createthread(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	listener;
	int			i;

	i = 0;
	if (pthread_create(&listener, NULL, &check, program->philos) != 0)
		clearall("Could not create thread", program, forks);
	while (i < program->philos[0].n_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philoroutine,
				&program->philos[i]) != 0)
			clearall("Could not create thread", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(listener, NULL) != 0)
		clearall("Could not join thread", program, forks);
	while (i < program->philos[i].n_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			clearall("Could not join thread", program, forks);
		i++;
	}
	return (0);
}
