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
	struct timeval	start;
	t_philo			*a;

	si = (int [3]){0, 0, 0};
	li = (long long int [2]){0, 0};
	si[0] = 0;
	pthread_mutex_lock(((t_m *) m)->mt3);
	a = (t_philo *)((t_m *) m)->b[si[0]];
	usleep(500 * 1000);
	si[0] += 1;
	pthread_mutex_unlock(((t_m *) m)->mt3);
	while (si[0] != *(((t_m *) m)->ph_n))
		;
	i = (int [2]){0, 0};
	i[0] = *a->phn;
	i[1] = 0;
	gettimeofday(&start, NULL);
	li[0] = get_time(start);
	si[1] = 0;
	si[2] = 0;
	while (si[1] != 1 && (*a->ecnt == -1 || si[2] < *a->ecnt * si[0]))
	{
		if (!me_dead(*((t_m *)m)->die_t, li[0], start))
		{
			pthread_mutex_lock(((t_m *) m)->mt1);
			if (*a->e->q == 1 && *a->d->q == 1 && *((t_m *)m)->ph_n != 1)
			{
				*a->e->q = 2;
				printf(P"%lld ms "Y"%d has taken a fork\n", get_time(start), i[0]);
				*a->d->q = 2;
				printf(P"%lld ms "Y"%d has taken a fork\n", get_time(start), i[0]);
				li[0] = get_time(start);
				pthread_mutex_unlock(((t_m *) m)->mt1);
				printf(P"%lld ms "G"%d is eating\n", get_time(start), i[0]);
				usleep(*((t_m *)m)->eat_t * 1000);
				if (*a->ecnt != -1)
					si[2] += 1;
				pthread_mutex_lock(((t_m *) m)->mt2);
				*a->e->q = 1;
				*a->d->q = 1;
				pthread_mutex_unlock(((t_m *) m)->mt2);
				i[1] = 1;
			}
			else if (*a->e->q == 1 && *a->d->q == 1 && *((t_m *)m)->ph_n == 1)
			{
				*a->e->q = 2;
				printf(P"%lld ms "Y"%d has taken a fork\n", get_time(start), i[0]);
				pthread_mutex_unlock(((t_m *) m)->mt1);
			}
			else
				pthread_mutex_unlock(((t_m *) m)->mt1);
			if (i[1] == 1 && si[1] != 1)
			{
				printf(P"%lld ms "C"%d is sleeping\n", get_time(start), i[0]);
				li[1] = get_time(start);
				while (get_time(start) - li[1] <= *((t_m *)m)->eat_t)
				{
					if (me_dead(*((t_m *)m)->die_t, li[0], start))
					{
						printf(P"%lld ms "R"%d died\n", get_time(start), i[0]);
						*a->status = 1;
						si[1] = 1;
						free(a->status);
						free(a->phn);
						free(a->ecnt);
						free(a);
						return (NULL);
					}
				}
				printf(P"%lld ms "B"%d is thinking\n", get_time(start), i[0]);
				i[1] = 0;
			}
		}
		else
		{
			*a->status = 1;
			si[1] = 1;
		}
	}
	if (*a->status == 1)
		printf(P"%lld ms "R"%d died\n"RE, get_time(start), i[0]);
	free(a->status);
	free(a->phn);
	free(a->ecnt);
	free(a);
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
