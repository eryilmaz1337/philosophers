/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:22:14 by eryilmaz          #+#    #+#             */
/*   Updated: 2022/06/07 18:22:16 by eryilmaz         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/philosophers.h"

int main(int index, char **data)
{
	t_simstatus sim;
	if (index == 6 || index == 5)
	{
		init(&sim, data);
		simi(&sim);
		free(sim.forks);
		free(sim.philosopher);
	}
	else
		printf("Lütfen girilen değerleri düzgün girin :)");
}
