#include "philo.h"

void start_simulation(t_table *table)
{
    int i = 0;
    while (i < table->num_philos)
    {
        pthread_create(&table->philos[i].thread, NULL, &routine, &table->philos[i]);
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

void clean_up(t_table *table)
{
    int i = 0;
    while (i < table->num_philos)
    {
        pthread_mutex_destroy(&table->forks[i]);
        pthread_mutex_destroy(&table->philos[i].meal_lock);
        i++;
    }
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->death_lock);
    free(table->forks);
    free(table->philos);
}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
    {
        printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [num_meals]\n");
        return (1);
    }
    if (atoi(argv[1]) > 200)
    {
        printf("too much philos\n");
        return (1);
    }
    t_table table;
    init_table(&table, argv);
    init_philosophers(&table);
    start_simulation(&table);
    clean_up(&table);

    return (0);
}