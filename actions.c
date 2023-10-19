/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcos- <amarcos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:00:06 by amarcos-          #+#    #+#             */
/*   Updated: 2023/10/19 08:41:54 by amarcos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philosophers *philosophers)
{
	messageunlock("is thinking", philosophers, philosophers->id);
}

void	dream(t_philosophers *philosophers)
{
	messageunlock("is sleeping", philosophers, philosophers->id);
	customusleep(philosophers->timetosleep);
}

void	eat(t_philosophers *philosophers)
{
	pthread_mutex_lock(philosophers->rfork);
	messageunlock("has taken a fork", philosophers, philosophers->id);
	if (philosophers->n_philos == 1)
	{
		customusleep(philosophers->timetodie);
		pthread_mutex_unlock(philosophers->rfork);
		return ;
	}
	pthread_mutex_lock(philosophers->lfork);
	messageunlock("has taken a fork", philosophers, philosophers->id);
	philosophers->eating = 1;
	messageunlock("is eating", philosophers, philosophers->id);
	pthread_mutex_lock(philosophers->meallock);
	philosophers->lastmeal = getcurrenttime();
	philosophers->meals++;
	pthread_mutex_unlock(philosophers->meallock);
	customusleep(philosophers->timetoeat);
	philosophers->eating = 0;
	pthread_mutex_unlock(philosophers->lfork);
	pthread_mutex_unlock(philosophers->rfork);
}
