/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualvare <gualvare@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:01:52 by gualvare          #+#    #+#             */
/*   Updated: 2025/03/26 14:53:33 by gualvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->table->print_lock);
	pthread_mutex_lock(&philo->table->death_lock);
	if (!philo->table->dead)
		printf("%ld %d %s\n", get_time() - philo->table->start_time,
			philo->id, status);
	pthread_mutex_unlock(&philo->table->death_lock);
	pthread_mutex_unlock(&philo->table->print_lock);
}

static	void	handle_one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	precise_sleep(philo, philo->table->time_to_die);
	pthread_mutex_lock(&philo->table->death_lock);
	philo->table->dead = 1;
	pthread_mutex_unlock(&philo->table->death_lock);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat(t_philo *philo)
{
	if (philo->table->num_philos == 1)
	{
		handle_one_philosopher(philo);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->meals_eaten == philo->table->meals_required)
	{
		pthread_mutex_lock(&philo->table->full_lock);
		philo->table->full++;
		pthread_mutex_unlock(&philo->table->full_lock);
	}
	precise_sleep(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		if (philo->table->dead)
		{
			pthread_mutex_unlock(&philo->table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
		eat(philo);
		print_status(philo, "is sleeping");
		precise_sleep(philo, philo->table->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	precise_sleep(t_philo *philo, long duration)
{
	long	start;

	start = get_time();
	while (get_time() - start < duration)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		if (philo->table->dead)
		{
			pthread_mutex_unlock(&philo->table->death_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->table->death_lock);
		if (get_time() - start >= duration)
			break ;
		usleep(500);
	}
}
