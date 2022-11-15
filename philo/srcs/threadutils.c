/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PHILOSOPHERS                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	forkaction(t_philo *a, long long int t, int i, int flag)
{
	if (flag == 0)
	{
		*a->e->q = 2;
		printf(P"%lld ms "Y"%d has taken a fork\n", t, i);
		*a->d->q = 2;
		printf(P"%lld ms "Y"%d has taken a fork\n", t, i);
		return ;
	}
	if (flag == 1)
	{
		*a->e->q = 2;
		printf(P"%lld ms "Y"%d has taken a fork\n", t, i);
		return ;
	}
	*a->e->q = 1;
	*a->d->q = 1;
	return ;
}

void	endthread(t_philo *a, long long int t, int i)
{
	if (*a->status == 1)
		printf(P"%lld ms "R"%d died\n"RE, t, i);
	free(a->status);
	free(a->phn);
	free(a->ecnt);
	free(a);
}
