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

// int array
// 0: philo number
// 1: sleeping or not
// //////////////////
// long long int array
// 0: time of last eat
// 1: time of last sleep
// //////////////////
// static int array
// 0: thread init check
// 1: death checker
// 2: eat counter
void	*f_thread(void *m)
{
	int				*i;
	long long int	*li;
	static int		*si;
	struct timeval	s;
	t_philo			*a;

	si = (int [3]){0, 0, 0};
	init_thread(m);
	a = (t_philo *)((t_m *) m)->b[si[0]++];
	while (si[0] != *(((t_m *) m)->ph_n))
		;
	i = (int [2]){*a->phn, 0};
	gettimeofday(&s, NULL);
	li = (long long int [2]){gt(s), 0};
	while (si[1] != 1 && (*a->ecnt == -1 || si[2] < *a->ecnt * si[0]))
	{
		if (!me_dead(*((t_m *)m)->die_t, li[0], s))
		{
			pthread_mutex_lock(((t_m *) m)->mt1);
			if (*a->e->q == 1 && *a->d->q == 1 && *((t_m *)m)->ph_n != 1)
			{
				li[0] = gt(s);
				i[1] = eat(a, ((t_m *)m), s, i);
				if (*a->ecnt != -1)
					si[2] += 1;
			}
			else if (*a->e->q == 1 && *a->d->q == 1 && *((t_m *)m)->ph_n == 1)
				forkaction(a, gt(s), i[0], ((t_m *)m));
			else
				pthread_mutex_unlock(((t_m *) m)->mt1);
			if (i[1] == 1 && si[1] != 1)
			{
				li[1] = gt(s);
				printf(P"%lld ms "C"%d is sleeping\n", gt(s), i[0]);
				while (gt(s) - li[1] <= *((t_m *)m)->sleep_t)
				{
					if (me_dead(*((t_m *)m)->die_t, li[0], s))
					{
						si[1] = philodied(a, gt(s), i[0], 1);
						printf("number on si[1] = %d\n", si[1]);
						return (NULL);
					}
				}
				printf(P"%lld ms "B"%d is thinking\n", gt(s), i[0]);
				i[1] = 0;
			}
		}
		else
			si[1] = philodied(a, gt(s), i[0], 0);
	}
	endthread(a, gt(s), i[0]);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_m	*m;

	if (inputcheck(ac, av) == 1)
		return (1);
	else
	{
		m = malloc(sizeof(t_m));
		masterbuilder(m, av);
		threaddoer(m, av);
		masterdestroyer(m);
		return (0);
	}
}
