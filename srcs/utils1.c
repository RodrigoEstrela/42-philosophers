#include "../inc/philo.h"

void printforks(t_forks *lst)
{
	t_forks *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("Fork: %d ", *tmp->fork);
		printf("Address: %p |", tmp->fork);
		tmp = tmp->next;
	}
	printf("\n");
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

void buildforks(t_forks **lst, int n)
{
	int i;
	int *content;

	i = 1;
	content = malloc(sizeof(int));
	*content = 1;
	*lst = NULL;
	ft_lstfront(lst, ft_lstnew(content));
	while (i < n)
	{
		content = malloc(sizeof(int));
		*content = 1;
		ft_lstadd_back(lst, ft_lstnew(content));
		i++;
	}
}

void	crono_thread(t_forks **forks)
{
	pthread_t	*t1;

	t1 = malloc(sizeof(pthread_t));
	pthread_create(t1, NULL, fThread_Timer, (void *) forks);

}