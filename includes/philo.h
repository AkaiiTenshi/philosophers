/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:13:51 by salsoysa          #+#    #+#             */
/*   Updated: 2025/08/07 20:01:24 by salsoysa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

//--------------------------------
/* -- [ Structs ] -- */
//--------------------------------

typedef enum s_time
{
	S,
	MILLI_S,
	MICRO_S,
}						t_time;

typedef enum s_code
{
	CREATE,
	INIT,
	JOIN,
	LOCK,
	UNLOCK,
	DESTROY,
	DETACH,
}						t_code;

typedef enum s_dinner
{
	THINKING,
	SLEEPING,
	EATING,
	TOOK_FORK1,
	TOOK_FORK2,
	DIED,
}						t_dinner;
/* -- Fork -- */
typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_i;
}						t_fork;

/* -- Data -- */
typedef struct s_data
{
	long				start;
	bool				end;
	bool				philos_r;
	long				nu_threads;
	long				nu_philo;
	long				ttd;
	long				tts;
	long				tte;
	long				max_meals;
	pthread_mutex_t		data_lock;
	pthread_mutex_t		print_lock;
	pthread_t			moni;
	t_fork				*forks;
	t_philo				*philos;
}						t_data;

/* -- Philo -- */
struct					s_philo
{
	long				nu_meals;
	long				last;
	bool				done;
	t_fork				*first_f;
	t_fork				*second_f;
	pthread_mutex_t		philo_lock;
	int					id;
	pthread_t			thread_i;
	t_data				*data;
};

//--------------------------------
/* -- [ Functions ] -- */
//--------------------------------

/* -- Core -- */
int						parse(t_data *data, char **av);
int						init(t_data *data);
void					printfoo(t_dinner state, t_philo *philo);
int						dinner_table(t_data *data);

/* -- Utils -- */
int						ft_print_error(char *str);
int						thread_foo(pthread_t *thread, void *(*foo)(void *),
							void *data, t_code type);
int						mutex_foo(pthread_mutex_t *mutex, t_code type);
long					get_time(t_time time);
void					better_usleep(long useconds, t_data *data);
bool					threads_up(pthread_mutex_t *mutex, long *threads,
							long nu_philo);
void					shift_philo(t_philo *philo);
void					iter_foo(pthread_mutex_t *mutex, long *nu);
void					*moni_foo(void *info);
void					clean(t_data *data);
void					thinking_routine(t_philo *philo);

/* -- Getters & Setters -- */
bool					stop_eating(t_data *data);
bool					boolean_get(pthread_mutex_t *mutex, bool *change);
void					boolean_set(pthread_mutex_t *mutex, bool change,
							bool *fresh);
void					long_set(pthread_mutex_t *mutex, long change,
							long *fresh);
long					long_get(pthread_mutex_t *mutex, long *change);
long					get_meals_count(t_philo *philo);
void					ft_get_philos_ready(t_data *data);

#endif
