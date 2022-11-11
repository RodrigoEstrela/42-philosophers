#include "../inc/philo.h"

pthread_mutex_t mt1, mt2;

int ft_atoi(const char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

long long int seconds_to_miliseconds(struct timeval t)
{
	long long int res;

	res = t.tv_sec * 1000;
	res += t.tv_usec / 1000;
	return (res);
}

long long int get_time(struct timeval start)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - seconds_to_miliseconds(start));
}

int	me_nao_dead(char *die_time, long long int eat_time, struct timeval start)
{
	//printf("1 = %lld 2 = %d	\n", get_time(start) - eat_time, ft_atoi(die_time));
	if (get_time(start)	 - eat_time > ft_atoi(die_time))
		return (1);
	return (0);
}

void	*fThread(void *a)
{
	int				c;
	int				sleep;
	long long int	eat_time;
	struct timeval	start;

	c = *(int *) ((t_philo *) a)->ind;
	sleep = 0;
	gettimeofday(&start, NULL);
	eat_time = get_time(start);
	while (!me_nao_dead(((t_philo *)a)->args[2], eat_time, start))
	{
		pthread_mutex_lock(&mt1);
		if (*((t_philo *)a)->esq->fork == 1)
		{
			*((t_philo *)a)->esq->fork = 2;
//			printf(PURPLE"%lld ms "YELLOW"%d has taken a fork\n"RESET, get_time(start), c + 1);
			if(*((t_philo *)a)->dir->fork == 1)
			{
				*((t_philo *)a)->dir->fork = 2;
				printf(PURPLE"%lld ms "YELLOW"%d has taken a fork\n"RESET, get_time(start), c + 1);
				eat_time = get_time(start);
				pthread_mutex_unlock(&mt1);
				printf(PURPLE"%lld ms "GREEN"%d is eating\n"RESET, get_time(start), c + 1);
				usleep(ft_atoi(((t_philo *) a)->args[3]) * 1000);
				pthread_mutex_lock(&mt2);
				*((t_philo *)a)->esq->fork = 1;
				*((t_philo *)a)->dir->fork = 1;
				pthread_mutex_unlock(&mt2);
				sleep = 1;
			}
			else
			{
				*((t_philo *)a)->esq->fork = 1;
				pthread_mutex_unlock(&mt1);
			}
		}
		else
			pthread_mutex_unlock(&mt1);
		if (sleep == 1)
		{
			printf(PURPLE"%lld ms "CYAN"%d is sleeping\n"RESET, get_time(start), c + 1);
			usleep(ft_atoi(((t_philo *) a)->args[4]) * 1000);
			sleep = 0;
			printf(PURPLE"%lld ms "BLUE"%d is thinking\n"RESET, get_time(start), c + 1);
		}
	}
	printf(PURPLE"%lld ms "RED"%d died\n"RESET, get_time(start), c + 1);
	free (((t_philo *)a)->ind);
	free(a);
	exit(0);
}

void *fThread_Timer(void *forks)
{
	struct timeval *t1;
	struct timeval *starttime;
	long long int time;

	(void)forks;
	t1 = malloc(sizeof(struct timeval));
	starttime = malloc(sizeof(struct timeval));
	gettimeofday(starttime, NULL);
	printf("Timer started %ld\n", starttime->tv_usec / 1000);
	long long int start = starttime->tv_sec * 1000 + (starttime->tv_usec / 1000);
	while (1)
	{
		usleep(100000);
		gettimeofday(t1, NULL);
		time = t1->tv_sec * 1000 + (t1->tv_usec / 1000);
		printf("Time: %lld\n", time - start);
//		printforks(*(t_forks **)forks);
//		printf("###########################\n");
	}
	free(t1);
}

int main(int ac, char **av)
{
	int				i;
	t_philo 		*a;
	pthread_t		th[124535];
	t_forks 		**forks;

	if (ac != 5)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	forks = malloc(sizeof(t_forks *));
	buildforks(forks, ft_atoi(av[1]));
	i = 0;
	pthread_mutex_init(&mt1, NULL);
	pthread_mutex_init(&mt2, NULL);
	while (i < ft_atoi(av[1]))
	{
		a = malloc(sizeof (t_philo));
		a->mt = malloc(sizeof(pthread_mutex_t));
		a->esq = NULL;
		a->dir = NULL;
		a->esq = getfork(*forks, i);
		if (i == ft_atoi(av[1]) - 1) {
			a->dir = getfork(*forks, 0);
		}
		else {
			a->dir = getfork(*forks, i + 1);
		}
		a->ind = malloc(sizeof (int));
		a->args = av;
		*a->ind = i;
		pthread_create(&th[i], NULL, &fThread, a);
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mt1);
	pthread_mutex_destroy(&mt2);
//	free(a);
	return (0);
}
