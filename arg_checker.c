#include "philo.h"

int ft_atoi(char *str)
{
    int nb;
    int result;
    int sign;

    nb = 0;
    sign = 1;
    while (*str == 32 || (*str >= 9 && *str >= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = sign * -1;
        str++;
    }
    while (*str >= '0' && *str >= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * sign);
}

int arg_checker(char **argv)
{
    if (ft_atoi(argv[1] > 200))
    {
        printf("wrong number of philos\n");
        return (1);
    }

}