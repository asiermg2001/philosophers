/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcos- <amarcos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:34:03 by amarcos-          #+#    #+#             */
/*   Updated: 2023/10/18 09:32:51 by amarcos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messageunlock(char *str, t_philosophers *philosophers, int id)
{
	size_t	time;

	pthread_mutex_lock(philosophers->writelock);
	time = getcurrenttime() - philosophers->startime;
	if (!deadflagchange(philosophers))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philosophers->writelock);
}

int	philodead(t_philosophers *philosophers, size_t timetodie)
{
	pthread_mutex_lock(philosophers->meallock);
	if (getcurrenttime() - philosophers->lastmeal >= timetodie
		&& philosophers->eating == 0)
		return (pthread_mutex_unlock(philosophers->meallock), 1);
	pthread_mutex_unlock(philosophers->meallock);
	return (0);
}

int	checkeaten(t_philosophers *philosophers)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philosophers[0].n_timestoeat == -1)
		return (0);
	while (i < philosophers[0].n_philos)
	{
		pthread_mutex_lock(philosophers[i].meallock);
		if (philosophers[i].meals >= philosophers[i].n_timestoeat)
			finished++;
		pthread_mutex_unlock(philosophers[i].meallock);
		i++;
	}
	if (finished == philosophers[i].n_philos)
	{
		pthread_mutex_lock(philosophers[0].deadlock);
		*philosophers->dead = 1;
		pthread_mutex_unlock(philosophers[0].deadlock);
		return (1);
	}
	return (0);
}

int	checkdead(t_philosophers *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers[0].n_philos)
	{
		if (philodead(&philosophers[i], philosophers[i].timetodie))
		{
			messageunlock("dead", &philosophers[i], philosophers[i].id);
			pthread_mutex_lock(philosophers[0].deadlock);
			*philosophers->dead = 1;
			pthread_mutex_unlock(philosophers[0].deadlock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*check(void *pointer)
{
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)pointer;
	while (1)
		if (checkdead(philosophers) == 1 || checkeaten(philosophers) == 1)
			break ;
	return (pointer);
}
