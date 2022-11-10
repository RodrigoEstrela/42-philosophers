#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct s_philo{
	char			**args;
	int				*ind;
	int				*forks;
	pthread_mutex_t	*mt;
}					t_philo;

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

void	*fThread(void *a)
{
	int c = *(int *) ((t_philo *) a)->ind;
	int *esq;
	int *dir;

	esq = &((t_philo *) a)->forks[c];
	if (c == ft_atoi(((t_philo *) a)->args[1]) - 1)
		dir = &((t_philo *) a)->forks[0];
	else
		dir = &((t_philo *) a)->forks[c + 1];
	while (1)
	{
		pthread_mutex_lock(((t_philo *) a)->mt);
		if (*esq == 1 && *dir == 1)
		{
			*esq = 2;
			*dir = 2;
			printf("Philo number: %d is eating\n", c + 1);
			usleep(ft_atoi(((t_philo *) a)->args[2]) * 1000);
			printf("Philo number: %d is DONE eating\n", c + 1);
			*esq = 1;
			*dir = 1;
		}
		pthread_mutex_unlock(((t_philo *)a)->mt);
		usleep(ft_atoi(((t_philo *) a)->args[3]) * 1000);
	}
	free (((t_philo *)a)->ind);
	free(a);
	return (NULL);
}

void	fill_int_arr(int *arr, int size)
{
	int i;

	i = 0;
	while (i < size) {
		arr[i] = 1;
		i++;
	}
}

int main(int ac, char **av)
{
	int				i;
	t_philo 		*a;
	pthread_t		th[124535];
	int 			*forksprimeiros;

	if (ac != 4)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	if (ft_atoi(av[1]) == 1)
		return (0);
	i = 0;
	forksprimeiros = (int *)malloc(sizeof(int) * ft_atoi(av[1]));
	fill_int_arr(forksprimeiros, ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
//		usleep(500);
		a = malloc(sizeof (t_philo));
		a->mt = malloc(sizeof(pthread_mutex_t));
		a->forks = malloc(sizeof(int) * ft_atoi(av[1]));
		a->forks = forksprimeiros;
		pthread_mutex_init(a->mt, NULL);
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
	pthread_mutex_destroy(a->mt);
//	free(a);
	return (0);
}
