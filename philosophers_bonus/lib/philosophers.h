/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:23:47 by eryilmaz          #+#    #+#             */
/*   Updated: 2022/06/07 18:23:48 by eryilmaz         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<errno.h>
# include	<pthread.h>
# include	<sys/time.h>
# include	<stdbool.h>
# include	<semaphore.h>
# include	<fcntl.h>
# include	<sys/stat.h>
# include	<sys/wait.h>
# include	<signal.h>

typedef struct s_philosophers
{
	int			id;
	long long	last_eat;
	int			eat_count;
	pid_t		thread_id;
	bool		kill;
	struct s_simstatus *sim;
	pthread_t a;
} t_philosophers;

typedef struct s_simstatus
{
	int				philosophers_cont;
	int				philosophers_kill_time;
	int				philosophers_eat_time;
	int				philosophers_sleep_time;
	int				philosophers_eat_cont;
	long long		start_time;
	bool			all_eat;
	bool			died;
	bool			eat;
	sem_t			*printfstatus;
	sem_t			*forks;
	t_philosophers	*philosopher;
}	t_simstatus;

int	ft_atoi(char *str);
long long	get_time(void);
void f_wait(long long time);
void printer(t_simstatus *sim, int id, char *msg);
void simi(t_simstatus *sim);
void init(t_simstatus *sim, char **data);
void end_sim(t_simstatus *sim);
void *dead(void *data);
#endif