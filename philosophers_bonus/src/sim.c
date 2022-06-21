/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ultis1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:57:55 by eryilmaz          #+#    #+#             */
/*   Updated: 2022/06/14 15:57:57 by eryilmaz         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/philosophers.h"

static void ye(t_philosophers *philo)
{
	sem_wait(philo->sim->forks);
	printer(philo->sim, philo->id, "1.catali aldi");
	sem_wait(philo->sim->forks);
	printer(philo->sim, philo->id, "2.catali aldi");
	printer(philo->sim, philo->id, "yemek yiyor");
	philo->last_eat = get_time();
	philo->eat_count++;
	f_wait(philo->sim->philosophers_eat_time);
	sem_post(philo->sim->forks);
	sem_post(philo->sim->forks);
}

static void *eat(void *philo)
{
	t_philosophers *phil;
	bool status;
	status = true;
	phil = (t_philosophers *)philo;
	if (phil->id % 2 != 0)
		usleep(1000);
	pthread_create(&phil->a, NULL, dead, phil);
	while (phil->sim->died == false && status)
	{
		ye(phil);
		if(phil->sim->all_eat)
			status = false;
		printer(phil->sim, phil->id, "uyuyor");
		f_wait(phil->sim->philosophers_sleep_time);
		printer(phil->sim, phil->id, "düşünüyor");
	}
	exit(0);
}

void	*dead(void *data)
{
	int	i;
	t_philosophers *philo;

	philo = (t_philosophers *)data;
	while (!philo->sim->eat && !philo->sim->died)
	{
		i = -1;
		while (++i < philo->sim->philosophers_cont && !philo->sim->died)
		{
			//printf("lsst : %lldid:%d\n", philo->last_eat, philo->id);
			//printf("last eat : %lld\nkill : %d\ni : %i\n", philo[i].last_eat ,  philo->sim->philosophers_kill_time,i);
			if(get_time() - philo->last_eat > philo->sim->philosophers_kill_time)
			{
				printer(philo->sim, philo->id, "öldü");
				philo->sim->died = true;
				exit(1);
			}
			if(philo->sim->philosophers_eat_cont != -1 && philo->sim->philosopher->eat_count >= philo->sim->philosophers_eat_cont)
				philo->sim->all_eat = true;
		}
		usleep(50);
	}
	return (NULL);
}

void	simi(t_simstatus *sim)
{
	int i;
	t_philosophers *philo;

	philo = sim->philosopher;
	sim->start_time = get_time();
	i = 0;
	while (i< sim->philosophers_cont)
	{
		philo->thread_id = fork();
		if(philo->thread_id<0)
			exit(1);
		if(philo->thread_id == 0)
			eat(&philo[i]);
		i++;
	}
	end_sim(sim);
}