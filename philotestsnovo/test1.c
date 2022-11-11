#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

pthread_mutex_t mt;

typedef struct		s_forks {
	int				*fork;
	struct s_forks	*next;
} 					t_forks;

typedef struct s_philo{
	char			**args;
	int				*ind;
	t_forks 		*esq;
	t_forks 		*dir;
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
	int	c;

	c = *(int *) ((t_philo *) a)->ind;
//	usleep(500000);
	while (1)
	{
//		sleep(1);
		pthread_mutex_lock(&mt);//((t_philo *) a)->mt);
		if (*((t_philo *)a)->esq->fork == 1 && *((t_philo *)a)->dir->fork == 1)
		{
			*((t_philo *)a)->esq->fork = 2;
			*((t_philo *)a)->dir->fork = 2;
			printf("Philo number: %d is eating\n", c + 1);
			usleep(ft_atoi(((t_philo *) a)->args[2]) * 1000);
			printf("Philo number: %d is DONE eating\n", c + 1);
			*((t_philo *)a)->esq->fork = 1;
			*((t_philo *)a)->dir->fork = 1;
		}
		pthread_mutex_unlock(&mt);//((t_philo *)a)->mt);
		usleep(ft_atoi(((t_philo *) a)->args[3]) * 1000);
	}
	free (((t_philo *)a)->ind);
	free(a);
	return (NULL);
}

void *fThread_Timer()
{
	struct timeval *t1;

	t1 = malloc(sizeof(struct timeval));
	while (1)
	{
		usleep(20000);
		gettimeofday(t1, NULL);
		printf("Time: %lld\n", t1->tv_sec * 1000LL + t1->tv_usec / 1000);
	}
	free(t1);
}

void ft_lstadd_back(t_forks **lst, t_forks *new)
{
	t_forks *tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_forks *ft_lstnew(int *content)
{
	t_forks *new;

	new = malloc(sizeof(t_forks));
	if (!new)
		return (NULL);
	new->fork = content;
	new->next = NULL;
	return (new);
}

void buildforks(t_forks **lst, int n)
{
	int i;
	int *content;

	i = 0;
//	lst = NULL;
	content = malloc(sizeof(int));
	*content = 1;
	while (i < n)
	{
		ft_lstadd_back(lst, ft_lstnew(content));
		i++;
	}
}

t_forks *getfork(t_forks *lst, int n)
{
	int		i;
	t_forks	*tmp;

	i = 0;
	tmp = lst;
	while (i < n)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

void printforks(t_forks *lst)
{
	t_forks *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("Fork: %d ", *tmp->fork);
		tmp = tmp->next;
	}
	printf("\n");
}

int main(int ac, char **av)
{
	int				i;
	t_philo 		*a;
	pthread_t		th[124535];
	t_forks 		**forks;

	if (ac != 4)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	if (ft_atoi(av[1]) == 1)
		return (0);
	forks = malloc(sizeof(t_forks *));
	buildforks(forks, ft_atoi(av[1]));
	i = 0;
	pthread_mutex_init(&mt, NULL);
	while (i < ft_atoi(av[1]))
	{
		a = malloc(sizeof (t_philo));
		a->mt = malloc(sizeof(pthread_mutex_t));
//		pthread_mutex_init(a->mt, NULL);
		a->esq = NULL;
		a->dir = NULL;
		a->esq = getfork(*forks, i);
		if (i == ft_atoi(av[1]) - 1)
			a->dir = getfork(*forks, 0);
		else
			a->dir = getfork(*forks, i + 1);
		printf("Esq: %d Dir: %d\n", *a->esq->fork, *a->dir->fork);
		printforks(*forks);
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
	pthread_mutex_destroy(&mt);//a->mt);
//	free(a);
	return (0);
}
