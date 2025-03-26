/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:52:50 by gualvare          #+#    #+#             */
/*   Updated: 2025/03/26 14:48:19 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_table *table, t_philo *philo)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->meal_lock);
	time_since_meal = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_since_meal > table->time_to_die)
	{
		pthread_mutex_lock(&table->death_lock);
		table->dead = 1;
		pthread_mutex_unlock(&table->death_lock);
		pthread_mutex_lock(&table->print_lock);
		printf("%ld %d died\n", get_time() - table->start_time, philo->id);
		pthread_mutex_unlock(&table->print_lock);
		return (1);
	}
	return (0);
}

int	all_satisfied(t_table *table)
{
	int		satisfied;
	t_philo	*philo;

	satisfied = 0;
	philo = table->philos;
	while (philo < table->philos + table->num_philos)
	{
		pthread_mutex_lock(&philo->meal_lock);
		if (table->meals_required > 0 && philo->meals_eaten
			>= table->meals_required)
			satisfied++;
		pthread_mutex_unlock(&philo->meal_lock);
		philo++;
	}
	if (satisfied == table->num_philos)
	{
		pthread_mutex_lock(&table->death_lock);
		table->dead = 1;
		pthread_mutex_unlock(&table->death_lock);
		return (1);
	}
	return (0);
}

void	monitor(t_table *table)
{
	t_philo	*philo;

	while (1)
	{
		philo = table->philos;
		while (philo < table->philos + table->num_philos)
		{
			if (philo_died(table, philo))
				return ;
			philo++;
		}
		if (table->meals_required > 0 && all_satisfied(table))
			return ;
		usleep(1000);
	}
}
// void	monitor(t_table *table)
// {
// 	int		i;
// 	int		satisfied;
// 	long	time_since_meal;

// 	while (1)
// 	{
// 		satisfied = 0;
// 		i = 0;
// 		while (i < table->num_philos)
// 		{
// 			pthread_mutex_lock(&table->philos[i].meal_lock);
// 			time_since_meal = get_time() - table->philos[i].last_meal_time;
// 			if (table->meals_required > 0 && table->philos[i].meals_eaten
// 				>= table->meals_required)
// 				satisfied++;
// 			pthread_mutex_unlock(&table->philos[i].meal_lock);
// 			if (time_since_meal > table->time_to_die)
// 			{
// 				pthread_mutex_lock(&table->print_lock);
// 				printf("%ld %d died\n", get_time() - table->start_time,
// 					table->philos[i].id);
// 				pthread_mutex_lock(&table->death_lock);
// 				table->dead = 1;
// 				pthread_mutex_unlock(&table->death_lock);
// 				pthread_mutex_unlock(&table->print_lock);
// 				return ;
// 			}
// 			i++;
// 		}
// 		if (table->meals_required > 0 && satisfied == table->num_philos)
// 		{
// 			pthread_mutex_lock(&table->death_lock);
// 			table->dead = 1;
// 			pthread_mutex_unlock(&table->death_lock);
// 			return ;
// 		}
// 		usleep(1000);
// 	}
// }
