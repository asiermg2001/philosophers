/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcos- <amarcos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:54:08 by amarcos-          #+#    #+#             */
/*   Updated: 2023/10/19 08:40:36 by amarcos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define MAXPHILOS 300

typedef struct s_philosophers
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals;
	size_t			lastmeal;
	size_t			timetodie;
	size_t			timetoeat;
	size_t			timetosleep;
	size_t			startime;
	int				n_philos;
	int				n_timestoeat;
	int				*dead;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*writelock;
	pthread_mutex_t	*deadlock;
	pthread_mutex_t	*meallock;
}			t_philosophers;
typedef struct s_program
{
	int				deadflag;
	pthread_mutex_t	deadlock;
	pthread_mutex_t	meallock;
	pthread_mutex_t	writelock;
	t_philosophers	*philos;
}			t_program;

int		ft_atoi(char *str);

void	start(t_program *program, t_philosophers *philosophers);

size_t	getcurrenttime(void);

void	startforks(pthread_mutex_t *forks, int n_philosophers);

void	startphilosohpers(t_philosophers *philosophers, t_program *program,
			pthread_mutex_t *forks, char **argv);

void	*check(void *pointer);

void	clearall(char *str, t_program *program, pthread_mutex_t *forks);

void	messageunlock(char *str, t_philosophers *philosophers, int id);

void	think(t_philosophers *philosophers);

void	dream(t_philosophers *philosophers);

void	eat(t_philosophers *philosophers);

int		createthread(t_program *program, pthread_mutex_t *forks);

int		deadflagchange(t_philosophers *philosophers);

int		customusleep(size_t time);

#endif