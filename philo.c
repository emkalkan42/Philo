/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emkalkan <emkalkan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:14:43 by emkalkan          #+#    #+#             */
/*   Updated: 2024/07/26 10:14:43 by emkalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "libft/includes/libft.h"

typedef struct s_philosopher
{
	int id;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	long last_meal;
	int meals_eaten;
	struct s_data *data;
} t_philosopher;

typedef struct s_data
{
	int num_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_meals;
	pthread_mutex_t *forks;
	t_philosopher *philosophers;
	long start_time;
} t_data;

long current_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

void print_status(t_philosopher *philosopher, const char *status)
{
    long timestamp = current_time() - philosopher->data->start_time;
    pthread_mutex_lock(&print_mutex); // Lock before printing
    printf("%ld %d %s\n", timestamp, philosopher->id, status);
    pthread_mutex_unlock(&print_mutex); // Unlock after printing
}

void take_forks(t_philosopher *philosopher)
{
    if (philosopher->id % 2 == 0)
    {
        pthread_mutex_lock(philosopher->right_fork);
        print_status(philosopher, "has taken a fork");
        pthread_mutex_lock(philosopher->left_fork);
        print_status(philosopher, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philosopher->left_fork);
        print_status(philosopher, "has taken a fork");
        pthread_mutex_lock(philosopher->right_fork);
        print_status(philosopher, "has taken a fork");
    }
}


void put_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}

pthread_mutex_t meal_mutex = PTHREAD_MUTEX_INITIALIZER;

void eat(t_philosopher *philosopher)
{
    take_forks(philosopher);
    pthread_mutex_lock(&meal_mutex); // Lock when updating last meal time
    philosopher->last_meal = current_time();
    pthread_mutex_unlock(&meal_mutex); // Unlock after updating
    print_status(philosopher, "is eating");
    usleep(philosopher->data->time_to_eat * 1000);
    philosopher->meals_eaten++;
    put_forks(philosopher);
}


void sleep_and_think(t_philosopher *philosopher)
{
	print_status(philosopher, "is sleeping");
	usleep(philosopher->data->time_to_sleep * 500);
	print_status(philosopher, "is thinking");
	usleep(philosopher->data->time_to_sleep * 500);
}

void *philosopher_life(void *arg)
{
    t_philosopher *philosopher = (t_philosopher *)arg;

    //usleep(1000);
    while (1)
    {
        long current = current_time();
        long time_since_last_meal = current - philosopher->last_meal;
        if (time_since_last_meal >= philosopher->data->time_to_die)
        {
            print_status(philosopher, "\033[31mdied\033[0m");
            break;
        }
        eat(philosopher);
        if (philosopher->data->num_meals != -1 && philosopher->meals_eaten >= philosopher->data->num_meals)
        {
            print_status(philosopher, "\033[31mdied\033[0m");
            break;
        }
        sleep_and_think(philosopher);
    }

    return NULL;
}

void init_philosophers(t_data *data)
{
	int i;

	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philosophers[i].id = i + 1;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
		data->philosophers[i].last_meal = current_time();
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].data = data;
		i++;
	}
}

void start_simulation(t_data *data)
{
	int i;

	data->start_time = current_time();
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_create(&data->philosophers[i].thread, NULL, philosopher_life, &data->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return 1;
	}
	data.num_philosophers = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.num_meals = (argc == 6) ? ft_atoi(argv[5]) : -1;

	if (data.num_philosophers == 1)
	{
		printf("\033[31mdied\033[0m\n");
		return 1;
	}
	if (argc == 6)
	{
   		if (data.num_meals < 0)
    	{
    	    printf("Error: num_meals must be a positive integer or zero.\n");
    	    return 1;
    	}
	}
	if (data.num_philosophers <= 0 || data.time_to_die <= 0 || data.time_to_eat <= 0 || data.time_to_sleep <= 0)
	{
		printf("Error: All timing parameters must be positive integers.\n");
		return 1;
	}
	init_philosophers(&data);
	start_simulation(&data);
	free(data.philosophers);
	free(data.forks);
	return 0;
}


