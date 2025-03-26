// #include "philo.h"

// void monitor(t_table *table)
// {
//     while (1)
//     {
//         int i = 0;
//         while (i < table->num_philos)
//         {
//             pthread_mutex_lock(&table->philos[i].meal_lock);
//             long time_since_meal = get_time() - table->philos[i].last_meal_time;
//             pthread_mutex_unlock(&table->philos[i].meal_lock);

//             if (time_since_meal > table->time_to_die)
//             {
//                 pthread_mutex_lock(&table->print_lock);
//                 printf("%ld %d died\n", get_time() - table->start_time, table->philos[i].id);
//                 pthread_mutex_lock(&table->death_lock);
//                 table->dead = 1;
//                 pthread_mutex_unlock(&table->death_lock);
//                 pthread_mutex_unlock(&table->print_lock);
//                 return;
//             }
//             i++;
//         }
//         usleep(1000);
//     }
// }

#include "philo.h"

void monitor(t_table *table)
{
    while (1)
    {
        int i = 0;
        int satisfied = 0;

        while (i < table->num_philos)
        {
            pthread_mutex_lock(&table->philos[i].meal_lock);
            long time_since_meal = get_time() - table->philos[i].last_meal_time;

            if (table->meals_required > 0 && table->philos[i].meals_eaten >= table->meals_required)
                satisfied++;
            pthread_mutex_unlock(&table->philos[i].meal_lock);
            if (time_since_meal > table->time_to_die)
            {
                pthread_mutex_lock(&table->print_lock);
                printf("%ld %d died\n", get_time() - table->start_time, table->philos[i].id);
                pthread_mutex_lock(&table->death_lock);
                table->dead = 1;
                pthread_mutex_unlock(&table->death_lock);                
                pthread_mutex_unlock(&table->print_lock);
                return;
            }
            i++;
        }
        if (table->meals_required > 0 && satisfied == table->num_philos)
        {
            pthread_mutex_lock(&table->death_lock);
            table->dead = 1;
            pthread_mutex_unlock(&table->death_lock);
            return;
        }
        usleep(1000);
    }
}