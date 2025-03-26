# ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table t_table;

typedef struct s_philo
{
    int id;
    int meals_eaten;
    long last_meal_time;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t meal_lock;
    t_table *table;
} t_philo;

typedef struct s_table
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_required;
    int dead;
    int full;
    long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t death_lock;
    pthread_mutex_t full_lock;
    t_philo *philos;
} t_table;

long get_time();
void init_table(t_table *table, char **argv);
void init_philosophers(t_table *table);
void *routine(void *arg);
void print_status(t_philo *philo, char *status);
void start_simulation(t_table *table);
void monitor(t_table *table);
void clean_up(t_table *table);
void precise_sleep(t_philo *philo, long duration);

#endif