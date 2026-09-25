/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hishembekka <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:34:16 by hishembekka       #+#    #+#             */
/*   Updated: 2026/09/25 23:37:22 by hishembekka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_table	t_table;

/*
** first_fork / second_fork : ordre de prise des fourchettes, fixe a l'init
** (pairs : gauche puis droite, impairs : droite puis gauche) -> pas de
** cycle d'attente, donc pas de deadlock.
** mlock protege last_meal et meals_eaten (lus par le monitor).
*/
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	mlock;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_table			*table;
}	t_philo;

/*
** start_lock : protege start_ready et ready_count (depart synchronise).
** end_lock   : protege flag_simulation_ended.
** write_lock : un seul printf a la fois, rien n'est affiche apres "died".
** Les compteurs *_initialized permettent a ft_clear de ne liberer que ce
** qui a reellement ete cree, meme apres une erreur.
*/
struct s_table
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_time_to_eat;
	long			start_time;
	bool			start_ready;
	int				ready_count;
	pthread_mutex_t	start_lock;
	bool			flag_simulation_ended;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				nb_forks_initialized;
	int				nb_meals_locks_initialized;
	int				nb_philo_threads_initialized;
	bool			write_lock_initialized;
	bool			end_lock_initialized;
	bool			start_lock_initialized;
	pthread_t		monitor;
	bool			monitor_created;
};

/* parsing.c */
int		ft_parsing_validate(t_table *table, int argc, char **argv);

/* init.c */
int		ft_initialize(t_table *table);

/* simulation.c */
int		ft_simulation(t_table *table);

/* sync.c */
bool	ft_simulation_stopped(t_table *table);
void	ft_put_simulation_stopped(t_table *table);
void	ft_add_ready_count(t_table *table);
int		ft_wait_start_or_end(t_table *table);
int		ft_all_philos_ready(t_table *table);

/* routine.c */
void	*ft_philo_routine(void *arg);

/* actions.c */
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);

/* forks.c */
int		ft_take_forks(t_philo *philo);
void	ft_release_forks(t_philo *philo);
int		ft_eat_alone(t_philo *philo);

/* monitor.c */
void	*ft_monitor_routine(void *arg);

/* print.c */
int		ft_print_status(t_philo *philo, char *status, bool died);

/* time.c */
long	ft_get_time_now(void);
int		ft_usleep(long time_sleep_in_ms, t_table *table);

/* utils.c */
long	ft_atol_custom(char *str);
int		ft_error(char *msg);

/* clear.c */
void	ft_clear(t_table *table);

#endif
