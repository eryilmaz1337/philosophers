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
	pthread_mutex_lock(&philo->sim->forks[philo->left_fork_id]);
	printer(philo->sim, philo->id, "1.catali aldi");
	pthread_mutex_lock(&philo->sim->forks[philo->right_fork_id]);
	printer(philo->sim, philo->id, "2.catali aldi");
	printer(philo->sim, philo->id, "yemek yiyor");
	philo->last_eat = get_time();
	philo->eat_count++;
	f_wait(philo->sim->philosophers_eat_time);
	pthread_mutex_unlock(&philo->sim->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->sim->forks[philo->right_fork_id]);
}

static void *eat(void *philo)
{
	t_philosophers *phil;
	bool status;
	status = true;
	phil = (t_philosophers *)philo;
	if (phil->id % 2 != 0)
		usleep(1000);
	while (phil->sim->died == false && status)
	{
		ye(phil);
		if(phil->sim->all_eat)
			status = false;
		printer(phil->sim, phil->id, "uyuyor");
		f_wait(phil->sim->philosophers_sleep_time);
		printer(phil->sim, phil->id, "düşünüyor");
	}
	return (NULL);
}

static void	dead(t_simstatus *sim, t_philosophers *philo)
{
	int	i;
	
	while (!sim->eat && !sim->died)
	{
		i = -1;
		while (++i < sim->philosophers_cont && !sim->died)
		{
			if(get_time() - philo[i].last_eat > sim->philosophers_kill_time)
			{
				printer(philo->sim, philo->id, "öldü");
				sim->died = true;
			}
			usleep(100);
			if(sim->philosophers_eat_cont != -1 && sim->philosopher[0].eat_count >= sim->philosophers_eat_cont)
				sim->all_eat = true;
		}
	}
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
		pthread_create(&philo[i].thread_id, NULL, eat, &philo[i]);
		i++;
	}
	dead(sim, philo);
}