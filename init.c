#include "philo.h"

long get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void init_table(t_table *table, char **argv)
{
    table->num_philos = atoi(argv[1]);
    table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    table->meals_required = -1;
    if (argv[5])
        table->meals_required = atoi(argv[5]);
    table->dead = 0;
    table->full = 0;
    table->start_time = get_time();

    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
    table->philos = malloc(sizeof(t_philo) * table->num_philos);

    int i = 0;
    while (i < table->num_philos)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&table->print_lock, NULL);
    pthread_mutex_init(&table->death_lock, NULL);
    pthread_mutex_init(&table->full_lock, NULL);
}

void init_philosophers(t_table *table)
{
    int i = 0;
    while (i < table->num_philos)
    {
        table->philos[i].id = i + 1;
        table->philos[i].meals_eaten = 0;
        table->philos[i].last_meal_time = get_time();
        table->philos[i].left_fork = &table->forks[i];
        table->philos[i].right_fork = &table->forks[(i + 1) % table->num_philos];
        table->philos[i].table = table;
        pthread_mutex_init(&table->philos[i].meal_lock, NULL);
        i++;
    }
}