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
	sem_wait(sim->printfstatus);
	if (!sim->died)
	{
		printf("ms : %lli ", get_time() - sim->start_time);
		printf(" ps : %i %s\n", id, msg);
	}
	sem_post(sim->printfstatus);
}

void f_wait(long long time)
{
	bool status;
	long long t;
	status = true;
	t = get_time();
	while (status)
	{
		if (get_time() - t >= time)
			status = false;
		usleep(32);
	}
}

void end_sim(t_simstatus *sim)
{
	int exit_satatus;
	int i;

	exit_satatus = 0;
	i = -1;
	while (1)
	{
		waitpid(-1, &exit_satatus, 0);
		if(exit_satatus != 0)
		{
			i = -1;
			while (++i < sim->philosophers_cont)
				kill(sim->philosopher[i].thread_id, SIGKILL);
		}
	}
	sem_close(sim->forks);
	sem_close(sim->printfstatus);
	sem_unlink("./printf_status");
	sem_unlink("./sem");
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