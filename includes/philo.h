/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salsoysa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:13:51 by salsoysa          #+#    #+#             */
/*   Updated: 2025/07/28 15:54:02 by salsoysa         ###   ########.fr       */
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

//--------------------------------
/* -- [ Structs ] -- */
//--------------------------------

typedef enum s_enum
{
	CREATE,
	INIT,
	JOIN,
	LOCK,
	UNLOCK,
	DESTROY,
	DETACH,
}						t_enum;
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
    bool                philos_r;
	long				nu_philo;
	long				ttd;
	long				tts;
	long				tte;
	long				max_meals;
    pthread_mutex_t     mutex_data;
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

/* -- Utils -- */
int						ft_print_error(char *str);
int						thread_foo(pthread_t *thread, void *(*foo)(void *),
							void *data, t_enum type);
int						mutex_foo(pthread_mutex_t *mutex, t_enum type);

/* -- Getters & Setters -- */
bool    stop_eating(t_data *data);
bool    boolean_get(pthread_mutex_t *mutex, bool *change);
void    boolean_set(pthread_mutex_t *mutex, bool change, bool *fresh );
void    long_set(pthread_mutex_t *mutex, long change, long *fresh );
long    long_get(pthread_mutex_t *mutex, long *change);


#endif
