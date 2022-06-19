/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:09:36 by eryilmaz          #+#    #+#             */
/*   Updated: 2022/06/16 19:09:39 by eryilmaz         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/philosophers.h"

void	printer(t_simstatus *sim, int id, char *msg)
{
	pthread_mutex_lock(&sim->printfstatus);
	if (!sim->died)
	{
		printf("ms : %lli ", get_time() - sim->start_time);
		printf(" ps : %i %s\n", id, msg);
	}
	pthread_mutex_unlock(&sim->printfstatus);
}

void f_wait(long long time)
{
	bool status;
	long long t;
	status = true;
	t = get_time();
	while (status)
	{
		usleep(32);
		if (get_time() - t >= time)
			status = false;
	}
}

void end_sim(t_simstatus *sim)
{
	int	i;

	i = -1;
	while (++i < sim->philosophers_cont)
		pthread_join(sim->philosopher->thread_id, NULL);
	i = -1;
	while (++i < sim->philosophers_cont)
		pthread_mutex_destroy(&sim->forks[i]);
	free (sim->forks);
	free (sim->philosopher);
	pthread_mutex_destroy(&sim->printfstatus);
}

int	ft_atoi(char *str)
{
	int	d;
	int	s;

	d = 1;
	s = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			d = d * -1;
			str++;
		}
		else
			str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		s = (s * 10) + (*str - '0');
		str++;
	}
	return (s * d);
}

long long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
