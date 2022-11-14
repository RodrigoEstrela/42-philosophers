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

void	*f_thread(void *m)
{
	int				c;
	int				sleeping;
	long long int	eat_time;
	long long int	sleep_time;
	struct timeval	start;
	t_philo			*a;
	static int		ichk;
	static int		dchk;
	static int		echk;

	ichk = 0;
	pthread_mutex_lock(((t_master *) m)->mt3);
	a = (t_philo *)((t_master *) m)->b[ichk];
	usleep(500 * 1000);
	ichk++;
	pthread_mutex_unlock(((t_master *) m)->mt3);
	while (ichk != *(((t_master *) m)->ph_n))
		;
	c = *a->phn;
	sleeping = 0;
	gettimeofday(&start, NULL);
	eat_time = get_time(start);
	dchk = 0;
	echk = 0;
	while (dchk != 1 && (*a->ecnt == -1 || echk < *a->ecnt * ichk))
	{
		if (!me_dead(*((t_master *)m)->die_t, eat_time, start))
		{
			pthread_mutex_lock(((t_master *) m)->mt1);
			if (*a->esq->q == 1 && *a->dir->q == 1 && *((t_master *)m)->ph_n != 1)
			{
				*a->esq->q = 2;
				printf(PURPLE"%lld ms "YELLOW"%d has taken a fork\n"RESET, get_time(start), c);
				*a->dir->q = 2;
				printf(PURPLE"%lld ms "YELLOW"%d has taken a fork\n"RESET, get_time(start), c);
				eat_time = get_time(start);
				pthread_mutex_unlock(((t_master *) m)->mt1);
				printf(PURPLE"%lld ms "GREEN"%d is eating\n"RESET, get_time(start), c);
				usleep(*((t_master *)m)->eat_t * 1000);
				if (*a->ecnt != -1)
					echk++;
				pthread_mutex_lock(((t_master *) m)->mt2);
				*a->esq->q = 1;
				*a->dir->q = 1;
				pthread_mutex_unlock(((t_master *) m)->mt2);
				sleeping = 1;
			}
			else if (*a->esq->q == 1 && *a->dir->q == 1 && *((t_master *)m)->ph_n == 1)
			{
				*a->esq->q = 2;
				printf(PURPLE"%lld ms "YELLOW"%d has taken a fork\n"RESET, get_time(start), c);
				pthread_mutex_unlock(((t_master *) m)->mt1);
			}
			else
				pthread_mutex_unlock(((t_master *) m)->mt1);
			if (sleeping == 1 && dchk != 1)
			{
				printf(PURPLE"%lld ms "CYAN"%d is sleeping\n"RESET, get_time(start), c);
				sleep_time = get_time(start);
				while (get_time(start) - sleep_time <= *((t_master *)m)->eat_t)
				{
					if (me_dead(*((t_master *)m)->die_t, eat_time, start))
					{
						printf(PURPLE"%lld ms "RED"%d died\n"RESET, get_time(start), c);
						*a->status = 1;
						dchk = 1;
						free(a->status);
						free(a->phn);
						free(a);
						return (NULL);
					}
				}
				printf(PURPLE"%lld ms "BLUE"%d is thinking\n"RESET, get_time(start), c);
				sleeping = 0;
			}
		}
		else
		{
			*a->status = 1;
			dchk = 1;
		}
	}
	if (*a->status == 1)
		printf(PURPLE"%lld ms "RED"%d died\n"RESET, get_time(start), c);
	free(a->status);
	free(a->phn);
	free(a);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_master	*m;

	if (inputcheck(ac, av) == 1)
		return (1);
	else
	{
		m = malloc(sizeof(t_master));
		masterbuilder(m, av);
		threaddoer(m, av);
		masterdestroyer(m);
		return (0);
	}
}
