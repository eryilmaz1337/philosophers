/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ultis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:02:12 by eryilmaz          #+#    #+#             */
/*   Updated: 2022/06/11 16:02:14 by eryilmaz         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/philosophers.h"

static int	init_mutex(t_simstatus *sim)
{
	int	i;
	int status;

	i = sim->philosophers_cont;
	status = pthread_mutex_init(&sim->printfstatus, NULL);
	while (--i >= 0)
	{
		status = pthread_mutex_init(&sim->forks[i], NULL);
		if (status)
			return (status);
	}
	if(status)
		return (status);
	return(1);
}

static void	init_philosophers(t_simstatus *sim)
{
	int i;

	i = sim->philosophers_cont;
	while (--i >= 0)
	{
		sim->philosopher[i].id = i;
		sim->philosopher[i].left_fork_id = i;
		sim->philosopher[i].right_fork_id = (i + 1) % sim->philosophers_cont;
		sim->philosopher[i].last_eat = get_time();
		sim->philosopher[i].eat_count = 0;
		sim->philosopher[i].sim = sim;
	}
}

void	init(t_simstatus *sim, char **data)
{
	int	status;
	sim->philosophers_cont = atoi(data[1]);
	sim->philosophers_kill_time = ft_atoi(data[2]);
	sim->philosophers_eat_time = ft_atoi(data[3]);
	sim->philosophers_sleep_time = ft_atoi(data[4]);
	sim->all_eat = false;
	sim->died = false;
	if (data[5])
		sim->philosophers_eat_cont= ft_atoi(data[5]);
	else
		sim->philosophers_eat_cont = -1;
	if (sim->philosophers_cont <= 0 || sim->philosophers_kill_time <= 0
		|| sim->philosophers_eat_time <= 0 || sim->philosophers_sleep_time<=0)
	{
		printf("Girdin Parametreleri Kontrol Ediniz");
		exit(1);
	}
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philosophers_cont);
	sim->philosopher = malloc(sizeof(t_philosophers) * sim->philosophers_cont);
	status = init_mutex(sim);
	if(!status)
		printf("!! ERROR Mutex hatası. Hata Kodu: %d", status);
	init_philosophers(sim);
}
