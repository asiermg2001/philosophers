/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcos- <amarcos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:49:44 by amarcos-          #+#    #+#             */
/*   Updated: 2023/10/18 09:37:27 by amarcos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkcontent(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	checkargs(char **argv)
{
	if (ft_atoi(argv[1]) > MAXPHILOS || ft_atoi(argv[1]) <= 0
		|| checkcontent(argv[1]) == 1)
		return (write(2, "Invalid philosohper number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || checkcontent(argv[2]) == 1)
		return (write(2, " Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || checkcontent(argv[3]) == 1)
		return (write(2, " Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || checkcontent(argv[4]) == 1)
		return (write(2, " Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || checkcontent(argv[5]) == 1))
		return (write(2, "Inalid number of times a philosopher must eat\n", 51),
			1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philosophers	philosophers[MAXPHILOS];
	pthread_mutex_t	forks[MAXPHILOS];

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (checkargs(argv) == 1)
		return (1);
	start(&program, philosophers);
	startforks(forks, ft_atoi(argv[1]));
	startphilosohpers(philosophers, &program, forks, argv);
	createthread(&program, forks);
	clearall(NULL, &program, forks);
	return (0);
}
