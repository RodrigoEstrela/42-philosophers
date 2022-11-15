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

void	endthread(t_philo *a, long long int t, int i)
{
	if (*a->status == 1)
		printf(P"%lld ms "R"%d died\n"RE, t, i);
	free(a->status);
	free(a->phn);
	free(a->ecnt);
	free(a);
}

int	philodied(t_philo *a, long long int t, int i, int flag)
{
	if (flag == 0)
		*a->status = 1;
	else if (flag == 1)
	{
		*a->status = 1;
		printf(P"%lld ms "R"%d died\n"RE, t, i);
		free(a->status);
		free(a->phn);
		free(a->ecnt);
		free(a);
	}
	return (1);
}

void	forkaction(t_philo *a, long long int t, int i, t_m *m)
{
	if (i < 0)
	{
		*a->e->q = 2;
		printf(P"%lld ms "Y"%d has taken a fork\n", t, -i);
		*a->d->q = 2;
		printf(P"%lld ms "Y"%d has taken a fork\n", t, -i);
		return ;
	}
	if (i > 0 && i < 1000)
	{
		*a->e->q = 2;
		printf(P"%lld ms "Y"%d has taken a fork\n", t, i);
		pthread_mutex_unlock(m->mt1);
		return ;
	}
	*a->e->q = 1;
	*a->d->q = 1;
}

void	init_thread(t_m *m)
{
	pthread_mutex_lock(((t_m *) m)->mt3);
	usleep(500 * 1000);
	pthread_mutex_unlock(((t_m *) m)->mt3);
}

int	eat(t_philo *a, t_m *m, struct timeval s, int *i)
{
	forkaction(a, gt(s), -i[0], 0);
	pthread_mutex_unlock(((t_m *) m)->mt1);
	printf(P"%lld ms "G"%d is eating\n", gt(s), i[0]);
	usleep(*((t_m *)m)->eat_t * 1000);
	pthread_mutex_lock(((t_m *) m)->mt2);
	forkaction(a, gt(s), i[0] * 1000, m);
	pthread_mutex_unlock(((t_m *) m)->mt2);
	return (1);
}
