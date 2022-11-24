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

int	sleeper(t_m *m, t_tt *t, t_philo *a, int s)
{
	printf(P"%lld ms "C"%d is sleeping\n", gt(*t->s), t->i[0]);
	while (gt(*t->s) - t->li[1] <= *m->sleep_t && s == 0)
	{
		if (me_dead(*m->die_t, t->li[0], *t->s))
		{
			philodied(a, gt(*t->s), t->i[0], 1);
			free(t->i);
			free(t->s);
			free(t->li);
			free(t);
			return (1);
		}
	}
	printf(P"%lld ms "B"%d is thinking\n", gt(*t->s), t->i[0]);
	return (0);
}

void unllock(t_philo *a, t_m *m, t_tt *p)
{
	forkaction(a, gt(*p->s), p->i[0]);
	pthread_mutex_unlock(((t_m *)m)->mt1);
}