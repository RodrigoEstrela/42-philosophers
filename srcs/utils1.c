#include "../inc/philo.h"

void printforks(t_lst *lst)
{
	t_lst *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("Fork: %d ", *tmp->q);
		printf("Address: %p |", tmp->q);
		tmp = tmp->next;
	}
	printf("\n");
}

t_lst *get_item(t_lst *lst, int n, int flag)
{
	int		i;
	t_lst	*tmp;

	if (flag == 0)
		return	NULL;
	i = 0;
	tmp = lst;
	while (i < n)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

void buildlst(t_lst **lst, int n)
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

void	crono_thread(t_lst **forks)
{
	pthread_t	*t1;

	t1 = malloc(sizeof(pthread_t));
	pthread_create(t1, NULL, fThread_Timer, (void *) forks);
}

//int eatcounter(char **args, )