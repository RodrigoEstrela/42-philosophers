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

int	sleeper(t_m *m, t_tt *t, t_philo *a)
{
	printf(P"%lld ms "C"%d is sleeping\n", gt(*t->s), t->i[0]);
	while (gt(*t->s) - t->li[1] <= *m->sleep_t)
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

int	megacoiso(t_m *m, t_tt *p, t_philo *a)
{
	if (*a->e->q == 1 && *a->d->q == 1 && *((t_m *) m)->ph_n != 1)
	{
		p->li[0] = gt(*p->s);
		eat(a, ((t_m *) m), p, p->i);
		return (1);
	}
	else if (*a->e->q == 1 && *a->d->q == 1 && *((t_m *) m)->ph_n == 1)
	{
		forkaction(a, gt(*p->s), p->i[0]);
		return (2);
	}
	else
	{
		return (0);
	}
}