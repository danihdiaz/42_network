/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhontani <dhontani@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 20:07:15 by dhontani          #+#    #+#             */
/*   Updated: 2026/08/20 13:23:37 by dhontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_config
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	int		scheduler;
}	t_config;

typedef struct s_simulation	t_simulation;
typedef struct s_dongle		t_dongle;

typedef struct s_person
{
	int				number;
	int				compile_count;
	long			last_compile;
	t_dongle		*right;
	t_dongle		*left;
	t_simulation	*sim;
}	t_person;

typedef struct s_wait_node
{
	t_person			*person;
	long				arrival_time;
	long				burnout_deadline;
}	t_wait_node;

typedef struct s_heap
{
	t_wait_node	*nodes;
	int			current_size;
	int			capacity;
}	t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	lock;
	long			last_release;
	int				is_taken;
	pthread_cond_t	av_cond;
	t_heap			heap;
}	t_dongle;

typedef struct s_simulation
{
	t_config		*config;
	t_person		*people;
	t_dongle		*dongles;
	pthread_mutex_t	log_lock;
	pthread_mutex_t	compile_lock;
	pthread_cond_t	compile_signal;
	int				stop;
	pthread_mutex_t	stop_lock;
	long			start;
}	t_simulation;

int				parser(char **args, t_config *config);
long			get_time_ms(void);
t_simulation	*simulation_init(t_config *config);
void			*person_life(void *arg);
void			log_message(t_person *person, char *state);
int				get_dongles(t_person *person);
void			release_dongles(t_person *person);
struct timespec	ms_to_timespec(long time);
void			*monitor(void *arg);
int				check_stop(t_simulation *sim);
int				get_parent(int index);
int				get_left(int index);
int				get_right(int index);
void			swap_nodes(t_wait_node *new, t_wait_node *old);
int				has_priority(t_wait_node *new, t_wait_node *old, int mode);
void			swap_nodes(t_wait_node *new, t_wait_node *old);
int				has_priority(t_wait_node *new, t_wait_node *old, int mode);
void			heap_push(t_heap *heap, t_wait_node *new, int mode);
t_wait_node		heap_pop(t_heap *heap, int mode);
void			*heap_init(t_heap *heap, int capacity);
void			clean_dongles(t_simulation *sim);
void			clean_people(t_simulation *sim);
void			clean_simulation(t_simulation *sim);

#endif