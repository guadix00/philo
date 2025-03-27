/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:27:35 by gualvare          #+#    #+#             */
/*   Updated: 2025/03/26 15:04:55 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_create(&table->philos[i].thread, NULL, &routine,
				&table->philos[i]);
			i++;
	}
	monitor(table);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

void	clean_up(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->full_lock);
	free(table->forks);
	free(table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		printf("Usage:./philo philos timetodie timetoeat timetosleep [meal]\n");
		return (1);
	}
	if (arg_checker(argv))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	init_table(&table, argv);
	init_philosophers(&table);
	start_simulation(&table);
	clean_up(&table);
	return (0);
}
